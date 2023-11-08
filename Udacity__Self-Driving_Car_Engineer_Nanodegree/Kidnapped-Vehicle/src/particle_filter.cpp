/**
 * particle_filter.cpp
 *
 * Created on: Dec 12, 2016
 * Author: Tiffany Huang
 */

#include "particle_filter.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "map.h"
// #include <cmath>

#include "helper_functions.h"

using std::string;
using std::vector;


// The Multivariate-Gaussian probability density
// sig_x, sig_y - standard deviation for both x and y
// x_obs, y_obs - the observations in map coordinates from landmarks quiz and 
// mu_x, mu_y - are the coordinates of the nearest landmarks.
double multiv_prob(double sig_x, double sig_y, double x_obs, double y_obs,
                   double mu_x, double mu_y) {
  // calculate normalization term
  double gauss_norm;
  gauss_norm = 1 / (2 * M_PI * sig_x * sig_y);

  // calculate exponent
  double exponent;
  exponent = (pow(x_obs - mu_x, 2) / (2 * pow(sig_x, 2)))
               + (pow(y_obs - mu_y, 2) / (2 * pow(sig_y, 2)));
    
  // calculate weight using normalization terms and exponent
  double w;
  w = gauss_norm * exp(-exponent);
    
  return w;
}

// Homogenous Transformation into map coordinates 
LandmarkObs transform(LandmarkObs obs, Particle p) {
  LandmarkObs tobs;
  
  tobs.x = p.x + (cos(p.theta) * obs.x) - (sin(p.theta) * obs.y);
  tobs.y = p.y + (sin(p.theta) * obs.x) + (cos(p.theta) * obs.y);
  
  return tobs;
}

void ParticleFilter::init(double x, double y, double theta, double std[]) {
  /**
   * TODO: Set the number of particles. Initialize all particles to 
   *   first position (based on estimates of x, y, theta and their uncertainties
   *   from GPS) and all weights to 1. 
   * TODO: Add random Gaussian noise to each particle.
   * NOTE: Consult particle_filter.h for more information about this method 
   *   (and others in this file).
   */
  num_particles = 100;  // TODO: Set the number of particles
//   Random generator
  std::default_random_engine gen;
  
  // Create a normal (Gaussian) distribution for x, y, theta
  std::normal_distribution<double> dist_x(0, std[0]);
  std::normal_distribution<double> dist_y(0, std[1]);
  std::normal_distribution<double> dist_theta(0, std[2]);
  
  for (int i = 0; i < num_particles; ++i) {
    Particle p;
    p.id = i;
//     init with gps and add noise
    p.x = x + dist_x(gen);
    p.y = y + dist_y(gen);
    p.theta = theta + dist_theta(gen);
    p.weight = 1.0; 
    particles.push_back(p);
  }
   is_initialized = true;
}



void ParticleFilter::prediction(double delta_t, double std_pos[], 
                                double velocity, double yaw_rate) {
  /**
   * TODO: Add measurements to each particle and add random Gaussian noise.
   * NOTE: When adding noise you may find std::normal_distribution 
   *   and std::default_random_engine useful.
   *  http://en.cppreference.com/w/cpp/numeric/random/normal_distribution
   *  http://www.cplusplus.com/reference/random/default_random_engine/
   */
   //   Random generator
  std::default_random_engine gen;
  // Create a normal (Gaussian) distribution for x, y, theta
  std::normal_distribution<double> dist_x(0, std_pos[0]);
  std::normal_distribution<double> dist_y(0, std_pos[1]);
  std::normal_distribution<double> dist_theta(0, std_pos[2]);

  for (int i = 0; i < num_particles; ++i) {
    double x_ = 0;
    double y_ = 0;
    double theta_ = 0;
    
    if (fabs(yaw_rate) < 0.00001) {  
      x_ = velocity * delta_t * cos(particles[i].theta);
      y_ = velocity * delta_t * sin(particles[i].theta);
    } 
    else {
      x_ = velocity / yaw_rate * (sin(particles[i].theta + yaw_rate*delta_t) - sin(particles[i].theta));
      y_ = velocity / yaw_rate * (cos(particles[i].theta) - cos(particles[i].theta + yaw_rate*delta_t));
      theta_ = yaw_rate * delta_t;
    }
    
//     add motion and noise
    particles[i].x = particles[i].x + x_ + dist_x(gen);
    particles[i].y = particles[i].y + y_ + dist_y(gen);
    particles[i].theta = particles[i].theta + theta_ + dist_theta(gen);   
  }

}

void ParticleFilter::dataAssociation(vector<LandmarkObs> predicted, 
                                     vector<LandmarkObs>& observations) {
  /**
   * TODO: Find the predicted measurement that is closest to each 
   *   observed measurement and assign the observed measurement to this 
   *   particular landmark.
   * NOTE: this method will NOT be called by the grading code. But you will 
   *   probably find it useful to implement this method and use it as a helper 
   *   during the updateWeights phase.
   */
  for (int i=0; i < observations.size(); ++i) {

    double min_dist = -1;
    int id = -1;
    for (int j=0; j < predicted.size(); ++j) {
      //     calculate distance between observation and landmark to choose neighbour
      double distance = dist(observations[i].x, observations[i].y, predicted[j].x, predicted[j].y);
      if (min_dist == -1 || distance < min_dist) {
        min_dist = distance; 
        id = predicted[j].id;
      }
    }
    observations[i].id = id;
  }
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[], 
                                   const vector<LandmarkObs> &observations, 
                                   const Map &map_landmarks) {
  /**
   * TODO: Update the weights of each particle using a mult-variate Gaussian 
   *   distribution. You can read more about this distribution here: 
   *   https://en.wikipedia.org/wiki/Multivariate_normal_distribution
   * NOTE: The observations are given in the VEHICLE'S coordinate system. 
   *   Your particles are located according to the MAP'S coordinate system. 
   *   You will need to transform between the two systems. Keep in mind that
   *   this transformation requires both rotation AND translation (but no scaling).
   *   The following is a good resource for the theory:
   *   https://www.willamette.edu/~gorr/classes/GeneralGraphics/Transforms/transforms2d.htm
   *   and the following is a good resource for the actual equation to implement
   *   (look at equation 3.33) http://planning.cs.uiuc.edu/node99.html
   */
//   for each particle
  for (int i=0; i < particles.size(); ++i) {
//     vector for possible landmarks that are in sensor range
    vector<LandmarkObs> predicted;
    for (int j=0; j < map_landmarks.landmark_list.size(); ++j) {
      Map::single_landmark_s landm = map_landmarks.landmark_list[j];
//       check distance between particle and landmark
      double distance = dist(particles[i].x, particles[i].y, landm.x_f, landm.y_f);
//       if it is smaller than sensor range then add it to array
      if (distance < sensor_range) {
        LandmarkObs l;
        l.id = landm.id_i;
        l.x = landm.x_f;
        l.y = landm.y_f;
        predicted.push_back(l);
      }        
    }
//   vector of transformed observations   
    vector<LandmarkObs> tobs_land;
//   each observation transform
    for (int k=0; k < observations.size(); ++k) {
      LandmarkObs tobs = transform(observations[k], particles[i]);
      tobs_land.push_back(tobs); 
    }
   
//     associate each observations with predicted landmarks
    dataAssociation(predicted, tobs_land);  
//     calculate probability for each transformed observation and final probability
    double prob = 1.0;
    for (int l=0; l < tobs_land.size(); ++l) {
      for (int m=0; m < predicted.size(); ++m) {
        if (predicted[m].id == tobs_land[l].id) {
          prob = prob*multiv_prob(std_landmark[0], std_landmark[1], tobs_land[l].x, tobs_land[l].y, predicted[m].x, predicted[m].y);
        }
      }
    }
//     assign probability to particles weight
    particles[i].weight = prob;     
  }
}

void ParticleFilter::resample() {
  /**
   * TODO: Resample particles with replacement with probability proportional 
   *   to their weight. 
   * NOTE: You may find std::discrete_distribution helpful here.
   *   http://en.cppreference.com/w/cpp/numeric/random/discrete_distribution
   */
  vector<double> weights;
  for (int i = 0; i < num_particles; i++) {
    weights.push_back(particles[i].weight);
  }
  
  std::default_random_engine gen;
  std::uniform_real_distribution<> dist(0, 1);
  std::uniform_int_distribution<int> index_dist(0, num_particles-1);
  
//   vector for resampled particles
  std::vector<Particle> resampled_particles;
  int index = index_dist(gen);
  float beta = 0.0;
  float max_w = *std::max_element(weights.begin(), weights.end());  
//   resampling wheel
  for (int i = 0; i < num_particles; ++i) {
    beta = beta + dist(gen)* 2.0 * max_w;
    while (beta > weights[index]) {
      beta = beta - weights[index];
      index = (index + 1) % num_particles;
    }
    resampled_particles.push_back(particles[index]);
  }
  particles = resampled_particles;  
}

void ParticleFilter::SetAssociations(Particle& particle, 
                                     const vector<int>& associations, 
                                     const vector<double>& sense_x, 
                                     const vector<double>& sense_y) {
  // particle: the particle to which assign each listed association, 
  //   and association's (x,y) world coordinates mapping
  // associations: The landmark id that goes along with each listed association
  // sense_x: the associations x mapping already converted to world coordinates
  // sense_y: the associations y mapping already converted to world coordinates
  particle.associations= associations;
  particle.sense_x = sense_x;
  particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best) {
  vector<int> v = best.associations;
  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}

string ParticleFilter::getSenseCoord(Particle best, string coord) {
  vector<double> v;

  if (coord == "X") {
    v = best.sense_x;
  } else {
    v = best.sense_y;
  }

  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<float>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);  // get rid of the trailing space
  return s;
}
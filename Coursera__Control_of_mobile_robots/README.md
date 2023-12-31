<h1>Using PySimiam in Coursera &#8216;Control of mobile robots&#8217; course<a class="headerlink" href="#using-pysimiam-in-coursera-control-of-mobile-robots-course" title="Permalink to this headline">¶</a></h1>
<p>Welcome, Coursera students!</p>
<p>Last year, during the first installment of the &#8220;Control of Mobile Robots&#8221; class,
we have decided to build our own version of the robot simulator that doesn&#8217;t need
MATLAB. This year we have the exciting opportunity to make our simulator available
to all of the students of the course, thanks to Dr. Magnus Egerstedt and the team.</p>
<p>Our simulator is inspired by the original <a class="reference external" href="http://gritslab.gatech.edu/home/2013/10/sim-i-am/">Sim.I.Am</a> simulator, and the programming assignments, as well as the robot description
were taken directly from the Sim.I.Am manual by Jean-Pierre de la Croix.
Special thanks to him for his hard work.</p>
<div class="section" id="introduction">
<h2>Introduction<a class="headerlink" href="#introduction" title="Permalink to this headline">¶</a></h2>
<p>This manual is going to be your resource for using the simulator in the programming exercises for this course.</p>
<div class="section" id="installation">
<h3>Installation<a class="headerlink" href="#installation" title="Permalink to this headline">¶</a></h3>
<p>The lastest release of pySimiam for Coursera students is available from <a class="reference external" href="http://sourceforge.net/projects/pysimiam/files/coursera/">Sourceforge</a> under the name pysimiam-coursera-weekX.zip (where X is the corresponding week for the exercise).</p>
<p>Unzip the latest provided archive and you are good to go!
Run the simulator with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_weekX</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<div class="section" id="requirements">
<h4>Requirements<a class="headerlink" href="#requirements" title="Permalink to this headline">¶</a></h4>
<p>You will need a reasonably modern computer to run the robot simulator. While the simulator will run on hardware older than a Pentium 4, it will probably be a very slow experience. You will also need <a class="reference external" href="http://www.python.org/getit/">Python 2.7</a> and two libraries - <a class="reference external" href="http://www.scipy.org/Download">Numpy</a> for mathematics and <a class="reference external" href="http://www.riverbankcomputing.com/software/pyqt/download">PyQT</a> for the GUI.</p>
</div>
<div class="section" id="bug-reporting">
<h4>Bug Reporting<a class="headerlink" href="#bug-reporting" title="Permalink to this headline">¶</a></h4>
<p>If you run into a bug (issue) with the simulator, please provide a detailed description either in a message in the discussion forums, in an issue in the sourceforge <a class="reference external" href="http://sourceforge.net/p/pysimiam/tickets/">issue tracker</a> or in an email to the developers. The bug will get fixed and a new version of the simulator will be available at sourceforge.</p>
</div>
</div>
<div class="section" id="mobile-robot">
<h3>Mobile Robot<a class="headerlink" href="#mobile-robot" title="Permalink to this headline">¶</a></h3>
<p>The mobile robot you will be using in the programming exercises is the QuickBot. The QuickBot is equipped with 5 infrared (IR) range sensors. The QuickBot has a two-wheel differential drive system (two wheels, two motors) with a wheel encoder for each wheel. It is powered by two 4x AA battery packs on top and can be controlled via software on its embedded Linux computer, the BeagleBone Black. You can build the QuickBot yourself by following the hardware lectures in this course.</p>
<table border="1" class="docutils">
<colgroup>
<col width="53%" />
<col width="47%" />
</colgroup>
<tbody valign="top">
<tr class="row-odd"><td><img alt="_images/quickbot_simulated.png" class="first last" src="_images/quickbot_simulated.png" style="width: 400px;" />
</td>
<td><img alt="_images/quickbot-blue.png" class="first last" src="_images/quickbot-blue.png" style="width: 400px;" />
</td>
</tr>
<tr class="row-even"><td>The simulated QuickBot</td>
<td>The actual QuickBot</td>
</tr>
</tbody>
</table>
<p>The robot simulator recreates the QuickBot as faithfully as possible. For example, the range, output, and field of view of the simulated IR range sensors match the specifications in the datasheet for the actual Sharp GP2D120XJ00F infrared proximity sensors on the QuickBot.</p>
<div class="section" id="ir-range-sensors">
<span id="coursera-irsensors"></span><h4>IR Range Sensors<a class="headerlink" href="#ir-range-sensors" title="Permalink to this headline">¶</a></h4>
<p>You will have access to the array of five IR sensors that encompass the QuickBot. The orientation of IR sensors (relative to the body of the QuickBot, as shown in previous figure, is 90°, 45°, 0°, -45° and -90° degrees, respectively. IR range sensors are effective in the range 4 cm to 30 cm only. However, the IR sensors return raw values in the range of [0.4, 2.75]V instead of the measured distances. To complicate matters slightly, the BeagleBone Black digitizes the analog output voltage using a voltage divider and a 12-bit, 1.8V analog-to-digital converter (ADC). The following is a look-up table to demonstrate the relationship between the ADC output, the analog voltage from the IR proximity sensor, and the approximate distance that corresponds to this voltage.</p>
<table border="1" class="docutils">
<colgroup>
<col width="33%" />
<col width="33%" />
<col width="33%" />
</colgroup>
<thead valign="bottom">
<tr class="row-odd"><th class="head">Distance (m)</th>
<th class="head">Voltage (V)</th>
<th class="head">ADC out</th>
</tr>
</thead>
<tbody valign="top">
<tr class="row-even"><td>0.04</td>
<td>2.750</td>
<td>917</td>
</tr>
<tr class="row-odd"><td>0.05</td>
<td>2.350</td>
<td>783</td>
</tr>
<tr class="row-even"><td>0.06</td>
<td>2.050</td>
<td>683</td>
</tr>
<tr class="row-odd"><td>0.07</td>
<td>1.750</td>
<td>583</td>
</tr>
<tr class="row-even"><td>0.08</td>
<td>1.550</td>
<td>517</td>
</tr>
<tr class="row-odd"><td>0.09</td>
<td>1.400</td>
<td>467</td>
</tr>
<tr class="row-even"><td>0.10</td>
<td>1.275</td>
<td>425</td>
</tr>
<tr class="row-odd"><td>0.12</td>
<td>1.075</td>
<td>358</td>
</tr>
<tr class="row-even"><td>0.14</td>
<td>0.925</td>
<td>308</td>
</tr>
<tr class="row-odd"><td>0.16</td>
<td>0.805</td>
<td>268</td>
</tr>
<tr class="row-even"><td>0.18</td>
<td>0.725</td>
<td>242</td>
</tr>
<tr class="row-odd"><td>0.20</td>
<td>0.650</td>
<td>217</td>
</tr>
<tr class="row-even"><td>0.25</td>
<td>0.500</td>
<td>167</td>
</tr>
<tr class="row-odd"><td>0.30</td>
<td>0.400</td>
<td>133</td>
</tr>
</tbody>
</table>
<p>Your supervisor can access the IR array through the <tt class="docutils literal"><span class="pre">robot_info</span></tt> object that is passed into the <tt class="docutils literal"><span class="pre">execute</span></tt> function. For example:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="k">for</span> <span class="n">i</span><span class="p">,</span> <span class="n">reading</span> <span class="ow">in</span> <span class="nb">enumerate</span><span class="p">(</span><span class="n">robot_info</span><span class="o">.</span><span class="n">ir_sensors</span><span class="o">.</span><span class="n">readings</span><span class="p">):</span>
    <span class="k">print</span> <span class="s">&#39;IR {} has a value of {}&#39;</span><span class="o">.</span><span class="n">format</span><span class="p">(</span><span class="n">i</span><span class="p">,</span> <span class="n">reading</span><span class="p">)</span>
</pre></div>
</div>
<p>To use the sensor readings, you will have to convert them to actual distances. For that you need to convert from the ADC output to an analog output voltage, and then from the analog output voltage to a distance in meters. The conversion from ADC output to analog output voltage is simply,</p>
<div class="math">
\[\begin{equation*}
  V_{\text{ADC}} = \left\lfloor\frac{1000\cdot V_{\text{analog}}}{3}\right\rfloor
\end{equation*}\]</div><p>Converting from the the analog output voltage to a distance is a little bit more complicated, because a) the relationships between analog output voltage and distance is not linear, and b) the look-up table provides a coarse sample of points.
You can use any way you like to convert between sensor readings and distances. For example, you can use the <a class="reference external" href="http://www.scipy.org/install.html">SciPy</a> mathematical library and interpolate the curve using <a class="reference external" href="http://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.interp1d.html#scipy-interpolate-interp1d">scipy.interpolate.inter1d</a>. Or you can fit the provided points with a high-degree polynomial and use this fit.</p>
<p>It is important to note that the IR proximity sensor on the actual QuickBot will be influenced by ambient lighting and other sources of interference. For example, under different ambient lighting conditions, the same analog output voltage may correspond to different distances of an object from the IR proximity sensor. The effect of ambient lighting (and other sources of noise) are <em>not</em> modelled in the simulator, but will be apparent on the actual hardware.</p>
<p>For the those curious to explain why IR sensors behave in an exponentially decaying manner: the intensity of the light decays in accordance to the <a class="reference external" href="http://en.wikipedia.org/wiki/Inverse-square_law">inverse square law</a>.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">In general, there is no need to know the exact indexing and number of the sensors, as all the information about the sensors is made available to the controllers and supervisors at runtime. In the best case, your code should be working even if the robot has 9 instead of 5 sensors.</p>
</div>
</div>
<div class="section" id="differential-wheel-drive">
<span id="coursera-diffdrivedyn"></span><h4>Differential Wheel Drive<a class="headerlink" href="#differential-wheel-drive" title="Permalink to this headline">¶</a></h4>
<p>Since the QuickBot has a differential wheel drive (i.e., is not a unicyle), it has to be controlled by specifying the angular velocities of the right and left wheel (<cite>v</cite><sub>l</sub>, <cite>v</cite><sub>r</sub>), instead of the linear and angular velocities of a unicycle <cite>(v, ω)</cite>. These velocities are computed by a transformation from <cite>(v, ω)</cite> to (<cite>v</cite><sub>l</sub>, <cite>v</cite><sub>r</sub>). Recall that the dynamics of the unicycle are defined as,</p>
<div class="math">
\[\begin{split}\frac{dx}{dt} &amp;= v\cos(\phi) \\
\frac{dy}{dt} &amp;= v\sin(\phi) \\
\frac{d\phi}{dt} &amp;= \omega\end{split}\]</div>
<p>The dynamics of the differential drive are defined as,</p>
<div class="math">
\[\begin{split}\frac{dx}{dt} &amp;= \frac{R}{2}(v_r + v_l)\cos(\phi) \\
\frac{dy}{dt} &amp;= \frac{R}{2}(v_r + v_l)\sin(\phi) \\
\frac{d\phi}{dt} &amp;= \frac{R}{L}(v_r - v_l)\end{split}\]</div>
<p>where <cite>R</cite> is the radius of the wheels and <cite>L</cite> is the distance between the wheels.</p>
<p>The speed for the QuickBot can be obtained in the following way assuming that you have implemented the <tt class="docutils literal"><span class="pre">uni2diff</span></tt> function, which transforms <cite>(v, ω)</cite> to (<cite>v</cite><sub>l</sub>, <cite>v</cite><sub>r</sub>):</p>
<div class="highlight-python"><div class="highlight"><pre><span class="n">v</span> <span class="o">=</span> <span class="mf">0.15</span> <span class="c"># m/s</span>
<span class="n">w</span> <span class="o">=</span> <span class="n">pi</span><span class="o">/</span><span class="mi">4</span> <span class="c"># rad/s</span>
<span class="c"># Transform from v,w to v_r,v_l</span>
<span class="n">vel_r</span><span class="p">,</span> <span class="n">vel_l</span> <span class="o">=</span> <span class="bp">self</span><span class="o">.</span><span class="n">uni2diff</span><span class="p">(</span><span class="n">v</span><span class="p">,</span><span class="n">w</span><span class="p">);</span>
</pre></div>
</div>
<p>The angular wheel velocity for the QuickBot is limited to about 80 RPM. It is important to note that if the QuickBot is controlled ot move at maximum linear velocity, it is not possible to achieve any angular velocity, because the angular velocity of the wheel will have been maximized. Therefore, there exists a tradeoff between the linear and angular velocity of the QuickBot: <em>the faster the robot should turn, the slower it has to move forward</em>.</p>
</div>
<div class="section" id="wheel-encoders">
<h4>Wheel Encoders<a class="headerlink" href="#wheel-encoders" title="Permalink to this headline">¶</a></h4>
<p>Each of the wheels is outfitted with a wheel encoder that increments or decrements a tick counter depending on whether the wheel is moving forward or backwards, respectively. Wheel encoders may be used to infer the relative pose of the robot. This inference is called <em>odometry</em>. The relevant information needed for odometry is the radius of the wheel, the distance between the wheels, and the number of ticks per revolution of the wheel. For example:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="n">R</span> <span class="o">=</span> <span class="n">robot_info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">radius</span> <span class="c"># radius of the wheel</span>
<span class="n">L</span> <span class="o">=</span> <span class="n">robot_info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">base_length</span> <span class="c"># distance between the wheels</span>
<span class="n">tpr</span> <span class="o">=</span> <span class="n">robot_info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">ticks_per_rev</span> <span class="c"># ticks per revolution for the wheels</span>

<span class="k">print</span> <span class="s">&#39;The right wheel has a tick count of {}&#39;</span><span class="o">.</span><span class="n">format</span><span class="p">(</span><span class="n">robot_info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">right_ticks</span><span class="p">)</span>
<span class="k">print</span> <span class="s">&#39;The left wheel has a tick count of {}&#39;</span><span class="o">.</span><span class="n">format</span><span class="p">(</span><span class="n">robot_info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">left_ticks</span><span class="p">)</span>
</pre></div>
</div>
</div>
</div>
</div>
<div class="section" id="week-1-getting-to-know-pysimiam">
<h2>Week 1. Getting to know pySimiam<a class="headerlink" href="#week-1-getting-to-know-pysimiam" title="Permalink to this headline">¶</a></h2>
<p>This week&#8217;s exercises will help you learn about Python and the robot simulator:</p>
<ol class="arabic simple">
<li>Since the programming exercises involve programming in Python, you should familiarize yourself with this language. Point your browser to <tt class="docutils literal"><span class="pre">http://docs.python.org/2/tutorial/</span></tt> to get an introduction to basic concepts.</li>
<li>Familiarize yourself with the simulator by reading the section on <a class="reference internal" href="tutorial.html#gui-tutorial"><em>Running pySimiam</em></a>, this manual and running the simulator script <tt class="docutils literal"><span class="pre">qtsimiam_week1.py</span></tt>.</li>
</ol>
<blockquote>
<div><ul class="simple">
<li>Try different view modes, like focusing on the robot and zooming</li>
<li>Change the parameters of the supervisor. For example, change the position of the goal and watch the robot direct itself towards it (to see the position of the goal you have to turn on supervisor info drawing). Also try changing the PID gains.</li>
<li>Crash you robot against a wall! The collision detection was not implemented in the supervisor, so the robot does not react to any obstacles and collides with them.</li>
</ul>
</div></blockquote>
<ol class="arabic simple" start="3">
<li>You are welcome to read the <a class="reference internal" href="code_user.html#user-api"><em>API documentation</em></a> of the simulator parts and look at the simulator&#8217;s code. The full understanding of the inner working is, however, not required to complete any of the assignments.</li>
</ol>
</div>
<div class="section" id="week-2-understanding-the-robot">
<h2>Week 2. Understanding the robot<a class="headerlink" href="#week-2-understanding-the-robot" title="Permalink to this headline">¶</a></h2>
<p>In this week&#8217;s exercises you will teach the supervisor to process the information from the robot.</p>
<img alt="_images/week2_null.png" class="align-left" src="_images/week2_null.png" style="width: 200px;" />
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week2</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>Alongside with the robot, some of the information provided by the supervisor is shown. The black dot in the middle of the robot is the current position of the robot, according to the supervisor. The arrow points in the direction of the goal angle (you can set it in supervisor properties). The crosses show the supervisor interpretation of the IR sensor signals. As your robot starts to move, you will also see two trajectories - one being the real trajectory of the robot, and the other calculated by the supervisor.</p>
<p>As you start the simulation for the first time, your robot will not move. To make it move, you will need to implement three components of the QuickBot supervisor, located in <tt class="docutils literal"><span class="pre">supervisors/week2.py</span></tt>. Remember, that it is not necessary to restart the simulator program every time you make change the code. It should suffice to restart the simulation, by pushing the blue double arrow button.</p>
<div class="section" id="transformation-from-unicycle-to-differential-drive-dynamics">
<h3>Transformation from unicycle to differential drive dynamics<a class="headerlink" href="#transformation-from-unicycle-to-differential-drive-dynamics" title="Permalink to this headline">¶</a></h3>
<p>The function used by the supervisor to convert from unicycle dynamics <cite>(v, ω)</cite> to differential drive dynamics (left and right <em>angular</em> wheel speeds (<cite>v</cite><sub>l</sub>, <cite>v</cite><sub>r</sub>)) is named <tt class="docutils literal"><span class="pre">uni2diff</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre>def uni2diff(self, uni):
    (v,w) = uni

    #Insert Week 2 Assignment Code Here

    # R = self.robot.wheels.radius
    # L = self.robot.wheels.base_length

    vl = 0
    vr = 0

    #End Week 2 Assignment Code

    return (vl, vr)
</pre></div>
</div>
<p>This function get as its input <tt class="docutils literal"><span class="pre">uni</span></tt>, a python tuple with two values. The function has to return left and right wheel speeds also as a tuple.</p>
<p>You are given the values:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">w</span></tt> (float) - angular velocity <em>ω</em></li>
<li><tt class="docutils literal"><span class="pre">v</span></tt> (float) - linear velocity <cite>v</cite></li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.radius</span></tt> (float) - <cite>R</cite>, the radius of robot&#8217;s wheels</li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.base_length</span></tt> (float) - <cite>L</cite>, the distance between wheels</li>
</ul>
<p>You have to set the values:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">vl</span></tt> (float) - angular velocity of the left wheel <cite>v</cite><sub>l</sub></li>
<li><tt class="docutils literal"><span class="pre">vr</span></tt> (float) - angular velocity of the right wheel <cite>v</cite><sub>r</sub></li>
</ul>
<p>Your job is to assign values to <tt class="docutils literal"><span class="pre">vl</span></tt> and <tt class="docutils literal"><span class="pre">vr</span></tt> such that the velocity and omega unicycle input correspond to the robot&#8217;s left and right wheel velocities. Please refer to section on <a class="reference internal" href="#coursera-diffdrivedyn"><em>Differential Wheel Drive</em></a> for the mathematical formulae.</p>
<div class="section" id="testing">
<h4>Testing<a class="headerlink" href="#testing" title="Permalink to this headline">¶</a></h4>
<p>With the <tt class="docutils literal"><span class="pre">uni2diff</span></tt> implemented, your robot will start to move as soon as you start the simulation, and as long as you don&#8217;t change the goal angle, it will move in a circle. If the goal angle is negative, the robot will move clockwise, if positive, counterclockwise, Note, that the supervisor perceives the robot as stanionary (the black dot doesn&#8217;t move with the robot). To change this, you need to implement odometry.</p>
</div>
</div>
<div class="section" id="odometry">
<h3>Odometry<a class="headerlink" href="#odometry" title="Permalink to this headline">¶</a></h3>
<p>Implement odometry for the robot, such that as the robot moves around, its pose <cite>(x, y, θ)</cite> is estimated based on how far each of the wheels have turned. Assume that the robot starts at (0,0,0).</p>
<p>The video lectures and, for example the <a class="reference external" href="www.orcboard.org/wiki/images/1/1c/OdometryTutorial.pdf">OrcBoard tutorial</a>, cover how odometry is computed. The general idea behind odometry is to use wheel encoders to measure the distance the wheels have turned over a small period of time, and use this information to approximate the change in pose of the robot.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">the video lecture may refer to robot&#8217;s orientation as <cite>ϕ</cite>.</p>
</div>
<p>The pose of the robot is composed of its position <cite>(x, y)</cite> and its orientation θ on a 2 dimensional plane. The currently estimated pose is stored in the variable <tt class="docutils literal"><span class="pre">self.pose_est</span></tt>, which bundles <tt class="docutils literal"><span class="pre">x</span></tt>, <tt class="docutils literal"><span class="pre">y</span></tt>, and <tt class="docutils literal"><span class="pre">theta</span></tt> (θ). The supervisor updates the estimate of its pose by calling the <tt class="docutils literal"><span class="pre">estimate_pose</span></tt> function. This function is called every <tt class="docutils literal"><span class="pre">dt</span></tt> seconds, where <tt class="docutils literal"><span class="pre">dt</span></tt> is 0.02s:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="k">def</span> <span class="nf">estimate_pose</span><span class="p">(</span><span class="bp">self</span><span class="p">):</span>

    #Insert Week 2 Assignment Code Here

    # Get tick updates
    #self.robot.wheels.left_ticks
    #self.robot.wheels.right_ticks

    # Save the wheel encoder ticks for the next estimate

    #Get the present pose estimate
    x, y, theta = self.pose_est

    #Use your math to update these variables...
    theta_new = 0
    x_new = 0
    y_new = 0

    #End Week 2 Assignment Code

    return Pose(x_new, y_new, (theta_new + pi)%(2*pi)-pi)
</div>
<p>You are given these variables:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.radius</span></tt> (float) - the radius of robot&#8217;s wheels</li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.base_length</span></tt> (float) - the distance between wheels</li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.ticks_per_rev</span></tt> (integer) - number of ticks registered per one full wheel revolution</li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.left_ticks</span></tt> (integer) - accumulated ticks on the left wheel</li>
<li><tt class="docutils literal"><span class="pre">self.robot.wheels.right_ticks</span></tt> (integer) - accumulated ticks on the right wheel</li>
</ul>
<p>Note that <tt class="docutils literal"><span class="pre">self.robot.wheels.left_ticks</span></tt> and <tt class="docutils literal"><span class="pre">.right_ticks</span></tt> represent
the tick numbering of the encoder and not the elapsed ticks. You will need
to implement a memory variable to store previous values and to calculate
the elapsed ticks. One example of how to do this might be:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="bp">self</span><span class="o">.</span><span class="n">prev_right_ticks</span> <span class="o">=</span> <span class="bp">self</span><span class="o">.</span><span class="n">robot</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">right_ticks</span>
<span class="bp">self</span><span class="o">.</span><span class="n">prev_left_ticks</span> <span class="o">=</span> <span class="bp">self</span><span class="o">.</span><span class="n">robot</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">left_ticks</span>
</pre></div>
</div>
<p>Note that <tt class="docutils literal"><span class="pre">self.prev_left_ticks</span></tt> and <tt class="docutils literal"><span class="pre">self.prev_right_ticks</span></tt> have to be initialized
in the constructor. The code is already in place for you in the <tt class="docutils literal"><span class="pre">__init__()</span></tt> method.</p>
<p>Your objective is to solve for the change in <cite>x</cite>, <cite>y</cite>, and <cite>θ</cite>
and from those values update the variables <cite>x_new</cite>, <cite>y_new</cite>, and <cite>theta_new</cite>.
The values <cite>x_new</cite>, <cite>y_new</cite>, and <cite>theta_new</cite> will be used to update
the estimated pose for the supervisor.</p>
<div class="section" id="id1">
<h4>Testing<a class="headerlink" href="#id1" title="Permalink to this headline">¶</a></h4>
<p>Congratulations! If you have implemented the odometry correctly, the robot moves around and aligns itself to the direction specified as goal angle. If it doesn&#8217;t, there are several ways  to debug your code. First, it is always possible to insert <tt class="docutils literal"><span class="pre">print</span></tt> statements anywhere in your program to put some output into the console. Inside the supervisor class, you can also use the <tt class="docutils literal"><span class="pre">self.log</span></tt> function to output information into the simulator log. Second, you can use the <a class="reference external" href="http://docs.python.org/2/library/pdb.html#module-pdb">Python debugger</a>. Note that the supervisor is running in a separate thread. Third, you can debug your supervisor graphically, by changing its <tt class="docutils literal"><span class="pre">draw</span></tt> function.</p>
</div>
</div>
<div class="section" id="convertion-from-raw-ir-values-to-distances-in-meters">
<h3>Convertion from raw IR values to distances in meters<a class="headerlink" href="#convertion-from-raw-ir-values-to-distances-in-meters" title="Permalink to this headline">¶</a></h3>
<p>The IR sensors return not the distance in meters, but a <cite>reading</cite>. To retrieve the distances measured by the IR proximity sensor, you will need to implement a conversion from the raw IR values to distances in the <tt class="docutils literal"><span class="pre">get_ir_distances</span></tt> function:</p>
<div class="highlight-python"><div class="highlight"><pre>def get_ir_distances(self):
    """Converts the IR distance readings into a distance in meters"""

    #Insert Week 2 Assignment Code Here

    ir_distances = [0]*len(self.robot.ir_sensors.readings) #populate this list

    #End Assignment week2

    return ir_distances
</pre></div>
</div>
<p>You are provided with the variable:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">self.robot.ir_sensors.readings</span></tt> (list of float) - the readings from QuickBot&#8217;s IR sensors</li>
</ul>
<img alt="_images/week2_full.png" class="align-left" src="_images/week2_full.png" style="width: 200px;" />
<p>The section on <a class="reference internal" href="#coursera-irsensors"><em>IR Range Sensors</em></a> contains a table with the values of readings for some sensor-object distances. You should interpolate these values and use you interpolation so that raw values in the range [200, 1375] are converted to distances in the range [0.04, 0.3] m. One simple way to do that is to use your favorite numeric analysis program and to fit the the provided points with a high-degree polynomial. The Numpy library, that you have already installed, can also be used to do the fitting, see the <a class="reference external" href="http://docs.scipy.org/doc/numpy/reference/routines.polynomials.polynomial.html">polynomial module</a>, especially the functions <cite>polyfit</cite> and <cite>polyval</cite>.</p>
<p>After the conversion is implemented, your robot should look like on the image on the left.</p>
<div class="section" id="id2">
<h4>Testing<a class="headerlink" href="#id2" title="Permalink to this headline">¶</a></h4>
<p>To test the IR sensor readings, we recommend to open another world file, <tt class="docutils literal"><span class="pre">week2ir.xml</span></tt>, from the simulator window. This world has five robots in it, all of which are close to different walls, and have different sets of IR sensors firing. You should see a black cross at the end of each sensor&#8217;s cone if you have implemented the conversion for each sensor correctly. In the case the conversion doesn&#8217;t work as expected, try printing the <tt class="docutils literal"><span class="pre">ir_distances</span></tt> array at the end of the <tt class="docutils literal"><span class="pre">get_ir_distances</span></tt> function and watch for errors.</p>
</div>
</div>

</div>
<div class="section" id="week-3-reaching-the-goal">
<h2>Week 3. Reaching the goal<a class="headerlink" href="#week-3-reaching-the-goal" title="Permalink to this headline">¶</a></h2>
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week3</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>You are encouraged (but not required) to reuse your code from week 2, by replacing the <tt class="docutils literal"><span class="pre">uni2diff</span></tt>, <tt class="docutils literal"><span class="pre">estimate_pose</span></tt> and <tt class="docutils literal"><span class="pre">get_ir_distances</span></tt> implementations in <tt class="docutils literal"><span class="pre">pysimiam/supervisors/quickbot.py</span></tt> with your solutions. Do not copy the complete file, as some of the other methods are different, and will break the simulation. Also, if you want to reuse your solution to <cite>get_ir_distances</cite>, note that the ADC conversion factor (and all ADC voltages from the table) has changed to 1000/3, as an earlier mistake was corrected.</p>
<p>This week, when you start the application, you will also get an additional window with a plot. When your simulation is running, the plot is automaticlaly updated, showing the time dependence of the robot heading direction and the angle from robot to goal. If you wish to see the time dependence of any other parameter, you can change the code of <tt class="docutils literal"><span class="pre">qtsimiam_week3.py</span></tt>. For example, currently the plotting code is:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="n">simWidget</span><span class="o">.</span><span class="n">add_graph</span><span class="p">([</span>
        <span class="p">[(</span><span class="s">&quot;Robot theta&quot;</span><span class="p">,</span> <span class="s">&quot;robot.get_pose().theta&quot;</span><span class="p">,</span> <span class="s">&#39;red&#39;</span><span class="p">),</span>
         <span class="p">(</span><span class="s">&quot;Angle to goal&quot;</span><span class="p">,</span><span class="s">&quot;math.atan2(supervisor.parameters.goal.y - robot.get_pose().y,supervisor.parameters.goal.x - robot.get_pose().x)&quot;</span><span class="p">,</span> <span class="s">&#39;blue&#39;</span><span class="p">)]</span>
        <span class="p">])</span>
</pre></div>
</div>
<p>To add another plot, for example, the time dependence of robot&#8217;s <cite>x</cite> and the goal <cite>x</cite> position, one can change that code like this:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="n">simWidget</span><span class="o">.</span><span class="n">add_graph</span><span class="p">([</span>
        <span class="p">[(</span><span class="s">&quot;Robot theta&quot;</span><span class="p">,</span> <span class="s">&quot;robot.get_pose().theta&quot;</span><span class="p">,</span> <span class="s">&#39;red&#39;</span><span class="p">),</span>
         <span class="p">(</span><span class="s">&quot;Angle to goal&quot;</span><span class="p">,</span><span class="s">&quot;math.atan2(supervisor.parameters.goal.y - robot.get_pose().y,supervisor.parameters.goal.x - robot.get_pose().x)&quot;</span><span class="p">,</span> <span class="s">&#39;blue&#39;</span><span class="p">)],</span>
        <span class="p">[(</span><span class="s">&quot;Robot X&quot;</span><span class="p">,</span> <span class="s">&quot;robot.get_pose().x&quot;</span><span class="p">,</span> <span class="s">&#39;red&#39;</span><span class="p">),</span>
         <span class="p">(</span><span class="s">&quot;Goal X&quot;</span><span class="p">,</span> <span class="s">&quot;supervisor.parameters.goal.x&quot;</span><span class="p">,</span><span class="s">&#39;blue&#39;</span><span class="p">)],</span>
        <span class="p">])</span>
</pre></div>
</div>
<p>If you do not see any plot windows, this means that none of the plotting engines could be loaded. You need one of the following libraries installed on your computer:</p>
<blockquote>
<div><ul class="simple">
<li><a class="reference external" href="http://www.scipy.org/install.html">SciPy</a> (this will enable the <a class="reference external" href="http://www.pyqtgraph.org/">PyQtGraph</a> library packaged with pySimiam)</li>
<li><a class="reference external" href="http://matplotlib.org/index.html">matplotlib</a></li>
<li><a class="reference external" href="http://pyqwt.sourceforge.net/">PyQwt</a></li>
</ul>
</div></blockquote>
<p>We recommend installing SciPy or matplotlib. matplotlib can draw somewhat nicer plots, but is also much slower.</p>
<p>Note that plots are not necessary for the assignments, as you can use the robot real and estimated trajectories to judge the quality of your PID controller.</p>
<div class="section" id="implementing-the-pid">
<h3>Implementing the PID<a class="headerlink" href="#implementing-the-pid" title="Permalink to this headline">¶</a></h3>
<p>This week you will be implementing the different parts of a PID regulator that steers the robot successfully to some goal location. This is known as the go-to-goal behavior. The controller that has to implement this behaviour is located at <tt class="docutils literal"><span class="pre">controllers/week3.py</span></tt>. The important methods to implement are <tt class="docutils literal"><span class="pre">restart</span></tt>, <tt class="docutils literal"><span class="pre">get_heading_angle</span></tt> and <tt class="docutils literal"><span class="pre">execute</span></tt></p>
<div class="highlight-python"><div class="highlight"><pre>def restart(self):
    #Week 3 Assignment Code:
    #Place any variables you would like to store here
    #You may use these variables for convenience
    self.E_k = 0 # Integrated error
    self.e_k_1 = 0 # Previous error calculation

    #End Week 3 Assigment

def get_heading_angle(self, state):
    """Get the heading angle in the world frame of reference."""

    #Insert Week 3 Assignment Code Here
    # Here is an example of how to get goal position
    # and robot pose data. Feel free to name them differently.

    #x_g, y_g = state.goal.x, state.goal.y
    #x_r, y_r, theta = state.pose

    return 0
    #End Week 3 Assigment

def execute(self, state, dt):
    """Executes avoidance behavior based on state and dt.
    state --> the state of the robot and the goal
    dt --> elapsed time
    return --> unicycle model list [velocity, omega]"""

    self.heading_angle = self.get_heading_angle(state)

    #Insert Week 3 Assignment Code Here

    # error between the heading angle and robot's angle
    e_k = 0

    # error for the proportional term
    e_P = 0

    # error for the integral term. Hint: Approximate the integral using
    # the accumulated error, self.E_k, and the error for
    # this time step, e_k.
    e_I = 0

    # error for the derivative term. Hint: Approximate the derivative
    # using the previous error, obj.e_k_1, and the
    # error for this time step, e_k.
    e_D = 0

    w_ = self.kp*e_P+ self.ki*e_I + self.kd*e_D

    v_ = state.velocity.v

    # save errors
    self.e_k_1 = e_k
    self.E_k = e_I

    #End Week 3 Assignment

    return [v_, w_]
</pre></div>
</div>
<p>In the <tt class="docutils literal"><span class="pre">restart</span></tt> function, the controller variables are initialized with the default values. It is called once at the creation of the controller, and possibly several times during its lifetime, in case the supervisor switches between two controllers. The direction to the goal is calculated in the <tt class="docutils literal"><span class="pre">get_heading</span></tt> function, that returns a vector pointing at the goal in the robot&#8217;s reference frame. This function is called in the <tt class="docutils literal"><span class="pre">execute</span></tt> function to steer the robot. The <tt class="docutils literal"><span class="pre">execute</span></tt> function is called every time the supervisor uses the go-to-goal behaviour. The following variables are available inside <tt class="docutils literal"><span class="pre">get_heading``and</span> <span class="pre">``execute</span></tt>:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">state.goal.x</span></tt> (float) - The X coordinate of the goal</li>
<li><tt class="docutils literal"><span class="pre">state.goal.y</span></tt> (float) - The Y coordinate of the goal</li>
<li><tt class="docutils literal"><span class="pre">state.pose</span></tt> (<a class="reference internal" href="code_simobject.html#pose.Pose" title="pose.Pose"><tt class="xref py py-class docutils literal"><span class="pre">Pose</span></tt></a>) - The position and orientation of the robot</li>
<li><tt class="docutils literal"><span class="pre">state.velocity.v</span></tt> (float) - The given target velocity of the robot.</li>
<li><tt class="docutils literal"><span class="pre">self.kp</span></tt> (float) - The proportional gain.</li>
<li><tt class="docutils literal"><span class="pre">self.ki</span></tt> (float) - The integral gain.</li>
<li><tt class="docutils literal"><span class="pre">self.kd</span></tt> (float) - The differential gain.</li>
</ul>
<p>To extract the pose data, you can use a command like this:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="p">(</span><span class="n">x</span><span class="p">,</span> <span class="n">y</span><span class="p">,</span> <span class="n">theta</span><span class="p">)</span> <span class="o">=</span> <span class="n">state</span><span class="o">.</span><span class="n">pose</span>
</pre></div>
</div>
<p>For those, who are curious where the <tt class="docutils literal"><span class="pre">state</span></tt> variable comes from: it is computed by <tt class="docutils literal"><span class="pre">Supervisor.get_controller_state()</span></tt>, that is reimplemented in <tt class="docutils literal"><span class="pre">QuickBotSupervisor</span></tt>. You can find additional information in the documentation for <a class="reference internal" href="controller.html#controller-tutorial"><em>Creating a controller</em></a> and in <a class="reference internal" href="code_sup_contr.html#controller.Controller" title="controller.Controller"><tt class="xref py py-class docutils literal"><span class="pre">Controller</span></tt></a> and <a class="reference internal" href="code_sup_contr.html#supervisor.Supervisor" title="supervisor.Supervisor"><tt class="xref py py-class docutils literal"><span class="pre">Supervisor</span></tt></a> API.</p>
<p>First, calculate the the heading angle for the robot. Let <cite>u</cite> be the vector from the robot located at <cite>(x,y)</cite> to the goal located at <cite>(x_g,y_g)</cite> in the world reference frame, then <cite>theta_g</cite> is the angle <cite>u</cite> makes with the <cite>x</cite>-axis (positive <cite>theta_g</cite> is in the counterclockwise direction). Use the <cite>x</cite> and <cite>y</cite> components of <cite>u</cite> and the <tt class="docutils literal"><span class="pre">math.atan2</span></tt> function to compute <cite>theta_g</cite>. <cite>theta_g</cite> has to be returned from the <tt class="docutils literal"><span class="pre">get_heading_angle</span></tt> method, to be used in <tt class="docutils literal"><span class="pre">execute</span></tt>.</p>
<p>Second, calculate the error between the obtained and the current heading angle of the robot in <cite>execute</cite>. Make sure to keep the error between [<cite>-π</cite>, <cite>π</cite>].</p>
<p>Third, calculate the proportional, integral, and derivative terms for the PID regulator that steers the robot to the goal.</p>
<p>As before, the robot will drive at a constant linear velocity <cite>v</cite>, but it is up to the PID regulator to steer the robot to the goal, i.e compute the correct angular velocity <em>ω</em>. The PID regulator needs three parts implemented:</p>
<blockquote>
<div><ol class="arabic simple">
<li>The first part is the proportional term <tt class="docutils literal"><span class="pre">e_P</span></tt>. It is simply the current error <tt class="docutils literal"><span class="pre">e_k</span></tt>. <tt class="docutils literal"><span class="pre">e_P</span></tt> is multiplied by the proportional gain <tt class="docutils literal"><span class="pre">self.kp</span></tt> when computing <tt class="docutils literal"><span class="pre">w</span></tt>.</li>
<li>The second part is the integral term <tt class="docutils literal"><span class="pre">e_I</span></tt>. The integral needs to be approximated in discrete time using the total accumulated error <tt class="docutils literal"><span class="pre">self.E_k</span></tt>, the current error <tt class="docutils literal"><span class="pre">e_k</span></tt>, and the time step <tt class="docutils literal"><span class="pre">dt</span></tt>. <tt class="docutils literal"><span class="pre">e_I</span></tt> is multiplied by the integral gain <tt class="docutils literal"><span class="pre">self.ki</span></tt> when computing <tt class="docutils literal"><span class="pre">w</span></tt>, and is also saved as <tt class="docutils literal"><span class="pre">self.E_k</span></tt> for the next time step.</li>
<li>The third part is the derivative term <tt class="docutils literal"><span class="pre">e_D</span></tt>. The derivative needs to be approximated in discrete time using the current error <tt class="docutils literal"><span class="pre">e_k</span></tt>, the previous error <tt class="docutils literal"><span class="pre">self.e_k_1</span></tt>, and the the time step <tt class="docutils literal"><span class="pre">dt</span></tt>. <tt class="docutils literal"><span class="pre">e_D</span></tt> is multiplied by the derivative gain <tt class="docutils literal"><span class="pre">self.kd</span></tt> when computing <tt class="docutils literal"><span class="pre">w</span></tt>, and the current error <tt class="docutils literal"><span class="pre">e_k</span></tt> is saved as the previous error <tt class="docutils literal"><span class="pre">self.e_k_1</span></tt> for the next time step.</li>
</ol>
</div></blockquote>
<p>Now, you need to tune your PID gains to get a fast settle time (<cite>θ</cite> matches <cite>θ</cite><sub>goal</sub> within 10% in three seconds or less) and there should be little overshoot (maximum <cite>θ</cite> should not increase beyond 10% of the reference value <cite>θ</cite><sub>goal</sub>). What you don&#8217;t want to see are the following two graphs when the robot tries to reach goal location <tt class="docutils literal"><span class="pre">(x_g,y_g)=(0,-1)</span></tt>:</p>
<div class="figure align-center">
<img alt="_images/week3GTG_overshooting.png" src="_images/week3GTG_overshooting.png" />
<p class="caption">Nearly 20% overshoot.</p>
</div>
<div class="figure align-center">
<img alt="_images/week3GTG_slowsettling.png" src="_images/week3GTG_slowsettling.png" />
<p class="caption">Undershoot - very large setting time.</p>
</div>
<div class="section" id="id5">
<h4>Testing<a class="headerlink" href="#id5" title="Permalink to this headline">¶</a></h4>
<p>To test your code, the simulator is set up to use the PID regulator in <tt class="docutils literal"><span class="pre">controllers/week3.py</span></tt> to drive the robot to a goal location. You can change the linear velocity of the robot, the gains and the goal location using the dock window on the right.</p>
<p>Make sure the goal is located inside the walls, i.e. the <cite>x</cite> and <cite>y</cite> coordinates of the goal should be in the range [-1.5, 1.5]. Otherwise the robot will crash into a wall on its way to the goal!</p>
<ol class="arabic simple">
<li>To test the heading to the goal, check that the green arrow points to the goal. You can also use a <tt class="docutils literal"><span class="pre">print</span></tt> statement, set the goal location to (1,1) and check that <tt class="docutils literal"><span class="pre">theta_g</span></tt> is approximately <span class="math">\(\frac{\pi}{4} \approx 0.785\)</span> initially, and as the robot moves forward (since <cite>v = 0.1</cite> and <cite>ω = 0</cite>) <tt class="docutils literal"><span class="pre">theta_g</span></tt> should increase.</li>
<li>To test the error calculation and the PID math, run the simulator and check if the robot drives to the goal location. The trajectory of the robot can be shown using the <cite>View &gt; Show/hide robot trajectories</cite> menu.</li>
</ol>
</div>
</div>
<div class="section" id="ensuring-the-right">
<h3>Ensuring the right <em>ω</em><a class="headerlink" href="#ensuring-the-right" title="Permalink to this headline">¶</a></h3>
<p>This week we&#8217;ll also tackle the first of two limitations of the motors on the QuickBot. The first limitation is that the robot&#8217;s motors have a maximum angular velocity, and the second limitation is that the motors stall at low speeds. We will discuss the latter limitation in a later week and focus our attention on the first limitation. Suppose that we pick a linear velocity <cite>v</cite> that requires the motors to spin at 90% power. Then, we want to change <em>ω</em> from 0 to some value that requires 20% more power from the right motor, and 20% less power from the left motor. This is not an issue for the left motor, but the right motor cannot turn at a capacity greater than 100%. The results is that the robot cannot turn with the <em>ω</em> specified by our controller.</p>
<p>Since our PID controllers focus more on steering than on controlling the linear velocity, we want to prioritize <em>ω</em> over <cite>v</cite> in situations, where we cannot satisfy <em>ω</em> with the motors. In fact, we will simply reduce <cite>v</cite> until we have sufficient headroom to achieve <em>ω</em> with the robot. The function <cite>ensure_w</cite> in <tt class="docutils literal"><span class="pre">supervisors/week3.py</span></tt> is designed to ensure that <em>ω</em> is achieved even if the original combination of <cite>v</cite> and <em>ω</em> exceeds the maximum <cite>vl</cite> and <cite>vr</cite>.</p>
<p>The code that needs to be completed is in <tt class="docutils literal"><span class="pre">supervisors/week3.py</span></tt>, in the method <tt class="docutils literal"><span class="pre">ensure_w</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre>def ensure_w(self,v_lr):

    v_l, v_r = v_lr

    #Week 3 Assignment Code:

    #End Week 3 Assigment

    return v_l, v_r
</pre></div>
</div>
<p><tt class="docutils literal"><span class="pre">v_lr</span></tt> is a tuple containing left and right wheel velocities <cite>v</cite><sub>l,d</sub> and <cite>v</cite><sub>r,d</sub>, as returned from <tt class="docutils literal"><span class="pre">uni2diff</span></tt>.  A motor&#8217;s maximum forward angular velocity is <tt class="docutils literal"><span class="pre">self.robot.wheels.max_velocity</span></tt> (<cite>v</cite><sub>max</sub>). You need to ensure that the two velocities <cite>v</cite><sub>l</sub> and <cite>v</cite><sub>r</sub> that are returned from <tt class="docutils literal"><span class="pre">ensure_w</span></tt> and sent to the robot do not exceed <cite>v</cite><sub>max</sub>. If <em>v</em> and/or <em>ω</em> are so large that <cite>v</cite><sub>l,d</sub> and/or <cite>v</cite><sub>r,d</sub> exceed <cite>v</cite><sub>max</sub>, then <cite>v</cite> needs to be reduced to ensure <em>ω</em> is achieved. If <em>ω</em> is larger than the maximum available angular velocity <em>ω</em><sub>max</sub>, you need to achieve at least <em>ω</em><sub>max</sub>.</p>
<p>Remember, <em>ω</em> is determined by the difference between the two wheel velocities, while <cite>v</cite> is proportional to their sum. Try to keep the difference the same, but decrease or increase the sum, so that <cite>v</cite><sub>l</sub> and <cite>v</cite><sub>r</sub> are both between -<cite>v</cite><sub>max</sub> and <cite>v</cite><sub>max</sub>. Consider the following diagrams:</p>
<div class="figure align-center">
<img alt="_images/ensure_w_0.png" src="_images/ensure_w_0.png" style="width: 400px;" />
<p class="caption">Both <cite>v</cite><sub>l,d</sub> and <cite>v</cite><sub>r,d</sub> are inside the range: no correction needed.</p>
</div>
<div class="figure align-center">
<img alt="_images/ensure_w_1.png" src="_images/ensure_w_1.png" style="width: 400px;" />
<p class="caption"><cite>v</cite><sub>r,d</sub> is outside of the range: both velocities should be shifted by <cite>v</cite><sub>r,d</sub> - <cite>v</cite><sub>max</sub>.</p>
</div>
<div class="figure align-center">
<img alt="_images/ensure_w_2.png" src="_images/ensure_w_2.png" style="width: 400px;" />
<p class="caption"><cite>v</cite><sub>l,d</sub> is outside the range: both velocities should be shifted by -<cite>v</cite><sub>l,d</sub> - <cite>v</cite><sub>max</sub>.</p>
</div>
<div class="figure align-center">
<img alt="_images/ensure_w_3.png" src="_images/ensure_w_3.png" style="width: 400px;" />
<p class="caption">Both <cite>v</cite><sub>l,d</sub> and <cite>v</cite><sub>r,d</sub> are outside of the range: <em>ω</em> &gt; <em>ω</em><sub>max</sub>.
We have to set <em>ω</em> = <em>ω</em><sub>max</sub> and <em>v</em> = 0.</p>
</div>
<div class="figure align-center">
<img alt="_images/ensure_w_4.png" src="_images/ensure_w_4.png" style="width: 400px;" />
<p class="caption">Only <cite>v</cite><sub>r,d</sub> is outside of the range, but again <em>ω</em> &gt; <em>ω</em><sub>max</sub>.
We have to set <em>ω</em> = <em>ω</em><sub>max</sub> and <em>v</em> = 0.</p>
</div>
<p>Note that the diagrams assume for simplicity that <cite>v</cite><sub>r,d</sub> &gt; <cite>v</cite><sub>l,d</sub>, that is <em>ω</em> &gt; 0.</p>
<div class="section" id="id6">
<h4>Testing<a class="headerlink" href="#id6" title="Permalink to this headline">¶</a></h4>
<p>Set the robot velocity to 10. If the robot does not turn with this settings, then <em>ω</em> is not ensured by <tt class="docutils literal"><span class="pre">ensure_w</span></tt>. Add <tt class="docutils literal"><span class="pre">print</span></tt> statements to check <tt class="docutils literal"><span class="pre">v_r</span> <span class="pre">-</span> <span class="pre">v_l</span></tt> (<em>ω</em>) and <tt class="docutils literal"><span class="pre">v_l</span> <span class="pre">+</span> <span class="pre">v_r</span></tt> (<cite>v</cite>) in the beginning and at the end of <tt class="docutils literal"><span class="pre">ensure_w</span></tt>.</p>
</div>
</div>
</div>
<div class="section" id="week-4-avoiding-obstacles">
<h2>Week 4. Avoiding obstacles<a class="headerlink" href="#week-4-avoiding-obstacles" title="Permalink to this headline">¶</a></h2>
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week4</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>In the case you want to reuse your code from week 3, please note that the PID code is now located in <tt class="docutils literal"><span class="pre">controllers/pid_controller.py</span></tt>. The <tt class="docutils literal"><span class="pre">execute</span></tt> method is using the heading from <tt class="docutils literal"><span class="pre">get_heading_angle</span></tt> to steer the robot. This heading is now in robot&#8217;s coordinates, meaning that the robot is steered to have a heading angle of 0. You can replace the <tt class="docutils literal"><span class="pre">reset</span></tt> and <tt class="docutils literal"><span class="pre">execute</span></tt> methods with your code, but do not forget to change the steering to robot&#8217;s coordinates.</p>
<p>The <tt class="docutils literal"><span class="pre">ensure_w</span></tt> method from last week is now located in <tt class="docutils literal"><span class="pre">supervisors/quickbot.py</span></tt>. The logic has been slightly changed, as detailed below in the section <a class="reference internal" href="#week4-ensure-w"><em>QuickBot motor limitations</em></a>.</p>
<div class="section" id="avoidobstacles-controller">
<h3>AvoidObstacles controller<a class="headerlink" href="#avoidobstacles-controller" title="Permalink to this headline">¶</a></h3>
<p>This week you will be implementing the different parts of a controller that steers the robot successfully away from obstacles to avoid a collision. This is known as the avoid-obstacles behavior. The IR sensors allow us to measure the distance to obstacles in the environment, but we need to compute the points in the world to which these distances correspond.</p>
<img alt="_images/week-4-ir-points.png" src="_images/week-4-ir-points.png" style="width: 300px;" />
<p>The figure illustrates these points with black crosses. The strategy for obstacle avoidance that we will use is as follows:</p>
<ol class="arabic simple">
<li>Transform the IR distances to points in the world.</li>
<li>Compute a vector to each point from the robot, <span class="math">\(u_0,u_1,\ldots,u_4\)</span>.</li>
<li>Weigh each vector according to their importance, <span class="math">\(\alpha_0u_0,\alpha_1u_1,\ldots,\alpha_4u_4\)</span>. For example, the front and side sensors are typically more important for obstacle avoidance while moving forward.</li>
<li>Sum the weighted vectors to form a single vector, <span class="math">\(u_o=\alpha_0u_0+\ldots+\alpha_4u_4\)</span>.</li>
<li>Use this vector to compute a heading and steer the robot to this angle.</li>
</ol>
<p>This strategy will steer the robot in a direction with the most free space (i.e., it is a direction <cite>away</cite> from obstacles). For this strategy to work, you will need to implement two crucial parts of the strategy for the obstacle avoidance behavior in the function <tt class="docutils literal"><span class="pre">get_heading</span></tt> in <tt class="docutils literal"><span class="pre">pysimiam/controllers/week4.py</span></tt> using the following information:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">self.sensor_poses</span></tt> (list of <a class="reference internal" href="code_simobject.html#pose.Pose" title="pose.Pose"><tt class="xref py py-class docutils literal"><span class="pre">Pose</span></tt></a>) - The positions and orientations of IR sensors in the reference frame of the robot</li>
<li><tt class="docutils literal"><span class="pre">self.kp</span></tt>, <tt class="docutils literal"><span class="pre">self.ki</span></tt> and <tt class="docutils literal"><span class="pre">self.kd</span></tt> - The PID gains of this controller</li>
<li><tt class="docutils literal"><span class="pre">state.sensor_distances</span></tt> (list of float) - The IR distances measured by each sensor</li>
<li><tt class="docutils literal"><span class="pre">state.pose</span></tt> (<a class="reference internal" href="code_simobject.html#pose.Pose" title="pose.Pose"><tt class="xref py py-class docutils literal"><span class="pre">Pose</span></tt></a>) - The position and orientation of the robot</li>
<li><tt class="docutils literal"><span class="pre">state.velocity.v</span></tt> (float) - The given target velocity of the simulation, which is usually the maximum available.</li>
</ul>
<p>The following code is in place:</p>
<div class="highlight-python"><div class="highlight"><pre>def get_heading(self, state):

    # Week 4 Assignment:

    # Calculate vectors:
    self.vectors = []

    # Calculate weighted sum:
    heading = [1, 0, 1]

    # End Week 4 Assignment

    return heading
</pre></div>
</div>
<p>First, transform the IR distance (which you converted from the raw IR values in Week 2) measured by each sensor to a point in the reference frame of the robot.</p>
<p>A point <span class="math">\(p_i\)</span> that is measured to be <span class="math">\(d_i\)</span> meters away by sensor <span class="math">\(i\)</span> can be written as the vector (coordinate) <span class="math">\(v_i=\begin{bmatrix}d_i \\ 0\end{bmatrix}\)</span> in the reference frame of sensor <span class="math">\(i\)</span>. We first need to transform this point to be in the reference frame of the robot. To do this transformation, we need to use the pose (location and orientation) of the sensor in the reference frame of the robot: <span class="math">\((x_{s_i},y_{s_i},\theta_{s_i})\)</span>. The transformation is defined as:</p>
<div class="math">
\[\begin{split}v'_i = R(x_{s_i},y_{s_i},\theta_{s_i})\begin{bmatrix}v_i \\ 1\end{bmatrix}\end{split}\]</div>
<p>where <span class="math">\(R\)</span> is known as the transformation matrix that applies a translation by <span class="math">\((x,y)\)</span> and a rotation by <span class="math">\(\theta\)</span>:</p>
<div class="math">
\[\begin{split}R(x,y,\theta) = \begin{bmatrix}
    \cos(\theta) &amp; -\sin(\theta) &amp; x \\
    \sin(\theta) &amp;  \cos(\theta) &amp; y \\
               0 &amp;             0 &amp; 1
    \end{bmatrix}.\end{split}\]</div>
<p>This matrix for a particular sensor can be obtained by calling the method <tt class="docutils literal"><span class="pre">get_transformation</span></tt> on the sensor&#8217;s pose. To construct the coordinates of the point in the sensor reference frame, use the <tt class="docutils literal"><span class="pre">numpy.array</span></tt> constructor. <tt class="docutils literal"><span class="pre">numpy.dot(a,b)</span></tt> implements the dot product of two matrices. Store the result of the transformation as a list of <span class="math">\(v'_i\)</span> vectors (or as a 2D array) in the variable <tt class="docutils literal"><span class="pre">self.vectors</span></tt>. The calculated vectors are now illustrated in the simulator by the black crosses. Note how these points <cite>approximately</cite> correspond to the distances measured by each sensor.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">The points do not exactly correspond to the distances because of how we converted from raw IR values to meters in Week 2).</p>
</div>
<p>Second, use the set of transformed points to compute a vector that points away from the obstacle. The robot will steer in the direction of this vector and successfully avoid the obstacle.</p>
<blockquote>
<div><ol class="arabic">
<li><p class="first">Pick a weight <span class="math">\(\alpha_i\)</span> for each vector according to how important you think a particular sensor is for obstacle avoidance. For example, if you were to multiply the vector from the robot to point <cite>i</cite> (corresponding to sensor <cite>i</cite>) by a small value (e.g., 0.1), then sensor <cite>i</cite> will not impact obstacle avoidance significantly. Set the weights in the constructor or in <tt class="docutils literal"><span class="pre">set_parameters</span></tt>.</p>
<blockquote>
<div><div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">Make sure to that the weights are symmetric with respect to the left and right sides of the robot. Without any obstacles around, the robot should only steer slightly right (due to a small asymmetry in the how the IR sensors are mounted on the robot).</p>
</div>
</div></blockquote>
</li>
<li><p class="first">Sum up the weighted vectors, <span class="math">\(\alpha_iv'_i\)</span>, into a single vector <span class="math">\(u_o\)</span> (for example using matrix multiplication).</p>
</li>
<li><p class="first">Return this vector as a heading away from obstacles (i.e., in a direction with free space, because the vectors that correspond to directions with large IR distances will contribute the most to <span class="math">\(u_o\)</span>).</p>
</li>
</ol>
</div></blockquote>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">Note that the heading vector should be define in robot&#8217;s coordinate system, not in the global one.</p>
</div>
<div class="section" id="id8">
<h4>Testing<a class="headerlink" href="#id8" title="Permalink to this headline">¶</a></h4>
<p>To test your code, the simulator is set up to use load the <tt class="docutils literal"><span class="pre">week4.py</span></tt> controller to drive the robot around the environment without colliding with any of the walls.
Here are some tips on how to test the three parts:</p>
<ol class="arabic simple">
<li>Once you have implemented the calculation of obstacle vectors, a black cross should match up with each sensor as shown in figure above. The robot should drive forward and collide with the wall.</li>
<li>Once you have implemented the steering, the robot should be able to successfully navigate the world without colliding with the walls (obstacles). If no obstacles are in range of the sensors, the red arrow (representing <span class="math">\(u_o\)</span>) should just point forward (i.e., in the direction the robot is driving). In the presence of obstacles, the red line should point away from the obstacles in the direction of free space.</li>
</ol>
<p>You can also tune the parameters of the PID regulator for <cite>ω</cite>.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">The red arrow (as well as the black crosses) will likely deviate from its position on the robot. The reason is that it are drawn with information derived from the odometry of the robot. The odometry of the robot accumulates error over time as the robot drives around the world. This odometric drift can be seen when information based on odometry is visualized via the lines and crosses.</p>
</div>
</div>
</div>
<div class="section" id="quickbot-motor-limitations">
<span id="week4-ensure-w"></span><h3>QuickBot motor limitations<a class="headerlink" href="#quickbot-motor-limitations" title="Permalink to this headline">¶</a></h3>
<p>Last week we implemented a function, <tt class="docutils literal"><span class="pre">ensure_w</span></tt>, which was responsible for respecting <cite>ω</cite> from the controller as best as possible by scaling <cite>v</cite> if necessary. This implementation assumed that it was possible to control the angular velocity in the range <tt class="docutils literal"><span class="pre">[-vel_max,</span> <span class="pre">vel_max]</span></tt>. This range reflected the fact that the motors on the QuickBot have a maximum rotational speed. However, it is also true that the motors have a minimum speed before the robot starts moving. If not enough power is applied to the motors, the angular velocity of a wheel remains at 0. Once enough power is applied, the wheels spin at a speed <tt class="docutils literal"><span class="pre">vel_min</span></tt>.</p>
<p>The <tt class="docutils literal"><span class="pre">ensure_w</span></tt> function has been updated this week to take this limitation into account. For example, small <tt class="docutils literal"><span class="pre">(v,ω)</span></tt> may not be achievable on the QuickBot, so <tt class="docutils literal"><span class="pre">ensure_w</span></tt> scales up <cite>v</cite> to make <cite>ω</cite> possible. Similarily, if <tt class="docutils literal"><span class="pre">(v,ω)</span></tt> are both large, <tt class="docutils literal"><span class="pre">ensure_w</span></tt> scales down <cite>v</cite> to ensure <cite>ω</cite> (as was the case last week). You can use the <tt class="docutils literal"><span class="pre">print</span></tt> statement to see <tt class="docutils literal"><span class="pre">(v,ω)</span></tt> before and after.</p>
<p>There is nothing that needs to be added or implemented for this week in <tt class="docutils literal"><span class="pre">ensure_w</span></tt>, but you may find it interesting how one deals with physical limitations on a mobile robot, like the QuickBot. This particular approach has an interesting consequence, which is that if <cite>v</cite> &gt; 0, then <cite>v_r</cite> and <cite>v_l</cite> are both positive (and vice versa, if <cite>v</cite> &lt; 0). Therefore, we often have to increase or decrease <cite>v</cite> significantly to ensure <cite>ω</cite> even if it were better to make small adjustments to both <cite>ω</cite> and <cite>v</cite>. As with most of the components in these programming assignments, there are alternative designs with their own advantages and disadvantages. Feel free to share your designs with everyone on the discussion forums!</p>
</div>

</div>
<div class="section" id="week-5-mixing-behaviours">
<h2>Week 5. Mixing behaviours<a class="headerlink" href="#week-5-mixing-behaviours" title="Permalink to this headline">¶</a></h2>
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week5</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>You are encouraged (but not required) to reuse your code from week 4, by replacing the <cite>set_parameters</cite> and <cite>get_heading</cite> method in <tt class="docutils literal"><span class="pre">controllers/avoidobstacles.py</span></tt> with your solutions. Note that the <tt class="docutils literal"><span class="pre">self.vectors</span></tt> variable is not needed anymore, so you can optimize your code further by getting rid of it, if you want.</p>
<p>This week you will be making a small improvement to the go-to-goal and avoid-obstacle controllers and testing two arbitration mechanisms: blending and hard switches. Arbitration between the two controllers will allow the robot to drive to a goal, while not colliding with any obstacles on the way.</p>
<div class="section" id="linear-velocity-dependent-on-angular-velocity">
<h3>Linear velocity dependent on angular velocity<a class="headerlink" href="#linear-velocity-dependent-on-angular-velocity" title="Permalink to this headline">¶</a></h3>
<p>So far, we have implemented controllers that either steer the robot towards a goal location, or steer the robot away from an obstacle. In both cases, we have set the linear velocity, <cite>v</cite>, to a constant value defined by the user. While this approach works, it certainly leaves plenty of room for improvement. We will improve the performance of both the go-to-goal and avoid-obstacles behavior by dynamically adjusting the linear velocity based on the angular velocity of the robot.</p>
<p>We previously learned that with a differential drive robot, we cannot, for example, drive the robot at the maximum linear and angular velocities. Each motor has a maximum and minimum angular velocity; therefore, there must be a trade-off between linear and angular velocities: linear velocity has to decrease in some cases for angular velocity to increase, and vice versa.</p>
<p>We added the <tt class="docutils literal"><span class="pre">ensure_w</span></tt> function over the last two weeks, which ensured that <em>ω</em> is achieved by scaling <em>v</em>. However, for example, one could improve the above strategy by letting the linear velocity be a function of the angular velocity <em>and</em> the distance to the goal (or distance to the nearest obstacle).</p>
<p>Improve your go-to-goal and avoid-obstacles controllers by adding a simple function that adjusts <em>v</em> as function of <em>ω</em> and other information. For example, the linear velocity in the go-to-goal controller could be scaled by <em>ω</em> and the distance to the goal, such that the robot slows down as it reaches the goal.</p>
<p>The right place to implement such adjustments is the :meth:<tt class="docutils literal"><span class="pre">~controller.Controller.execute</span></tt> function of both the GoToGoal controller in <tt class="docutils literal"><span class="pre">controllers/gotogoal.py</span></tt> and the AvoidObstacles controller in <tt class="docutils literal"><span class="pre">controllers/avoidobstacles.py</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre>def execute(self, state, dt):

    v, w = PIDController.execute(self, state, dt)

    # Week 5 code
    #
    #

    return v, w
</pre></div>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">This part of the programming assignment is open ended and not checked by the automatic grader, but it will help with the other parts of this assignment.</p>
</div>
</div>
<div class="section" id="blending-behaviours">
<h3>Blending behaviours<a class="headerlink" href="#blending-behaviours" title="Permalink to this headline">¶</a></h3>
<p>It&#8217;s time to implement the first type of arbitration mechanism between multiple controllers: <cite>blending</cite>. The solutions to the go-to-goal and avoid-obstacles controllers have been combined into a single controller <tt class="docutils literal"><span class="pre">controller/week5.py</span></tt>. However, one important piece (namely the implementation of <tt class="docutils literal"><span class="pre">get_heading</span></tt>) is missing:</p>
<div class="highlight-python"><div class="highlight"><pre>def get_heading(self, state):
    """Blend the two heading vectors"""

    # Get the outputs of the two subcontrollers
    u_ao = AvoidObstacles.get_heading(self,state)
    self.away_angle = math.atan2(u_ao[1],u_ao[0])
    u_ao = numpy.array([math.cos(self.away_angle),math.sin(self.away_angle),1])

    self.goal_angle = GoToGoal.get_heading_angle(self,state)
    u_gtg = numpy.array([math.cos(self.goal_angle),math.sin(self.goal_angle),1])

    # Week 5 Assigment Code goes here:

    u = u_gtg

    # End Week 5 Assigment

    return u
</pre></div>
</div>
<p>Here, <tt class="docutils literal"><span class="pre">u_gtg</span></tt> is a vector pointing to the goal from the robot, and <tt class="docutils literal"><span class="pre">u_ao</span></tt> is a vector pointing from the robot to a point in space away from obstacles. These two vectors need to be combined (blended) in some way into the vector <tt class="docutils literal"><span class="pre">u</span></tt>, which should be a vector that points the robot both away from obstacles and towards the goal. Both vectors are NumPy arrays and support arbitrary array operations. The vectors are normalized to have a length of 1.</p>
<p>The combination of the two vectors into <tt class="docutils literal"><span class="pre">u</span></tt> should result in the robot driving to a goal without colliding with any obstacles in the way. Do not use <tt class="docutils literal"><span class="pre">if/else</span></tt> to pick between <tt class="docutils literal"><span class="pre">u_gtg</span></tt> or <tt class="docutils literal"><span class="pre">u_ao</span></tt>, but rather think about weighing each vector according to their importance, and then linearly combining the two vectors into a single vector, <tt class="docutils literal"><span class="pre">u_ao_gtg</span></tt>. For example,</p>
<div class="math">
\[\begin{split}\alpha &amp;=&amp; 0.75 \\
u &amp;=&amp; \alpha u_{\mathrm{gtg}}+(1-\alpha)u_{\mathrm{ao}}\end{split}\]</div>
<p>In this example, the go-to-goal behavior is stronger than the avoid-obstacle behavior, but that <cite>may</cite> not be the best strategy. <cite>α</cite> needs to be carefully tuned (or a different weighted linear combination needs to be designed) to get the best balance between go-to-goal and avoid-obstacles. You may also want to adjust <em>v</em> for this controller, as you did for the other two in the previous part of the assignment.</p>
<div class="section" id="id10">
<h4>Testing<a class="headerlink" href="#id10" title="Permalink to this headline">¶</a></h4>
<p>To run the simulator with the blending supervisor use:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week5</span><span class="o">.</span><span class="n">py</span> <span class="n">blending</span>
</pre></div>
</div>
<p>You will see three arrows showing the information about different headings:</p>
<p>The green arrow is the heading returned by the GoToGoal controller, the red arrow - the heading returned by the AvoidObstacles controller. The blue arrow is the blended vector.</p>
<p>The robot should successfully navigate to the goal location (1,1) without colliding with the obstacle that is in the way. When the robot is near the goal, it will start circling around it. Don&#8217;t worry, this behaviour will be taken care of in the next part.</p>
</div>
</div>
<div class="section" id="switching-between-behaviours">
<h3>Switching between behaviours<a class="headerlink" href="#switching-between-behaviours" title="Permalink to this headline">¶</a></h3>
<p>The second type of arbitration mechanism is <cite>switching</cite>. Instead of executing both go-to-goal and avoid-obstacles simultaneously, we will only execute one controller at a time, but switch between the two controllers whenever a certain condition is satisfied.</p>
<p>You will need to implement the switching logic between go-to-goal and avoid-obstacles in <tt class="docutils literal"><span class="pre">supervisors/week5_switching.py</span></tt>. The supervisor has a built-in state machine to support switching between different controllers (or states, where a state simply corresponds to one of the controllers being executed). In order to switch between different controllers (or states), the supervisor has to define the switching conditions. These conditions are checked to see if they are true or false. The idea is to start of in some state (which runs a certain controller), check if a particular condition is fullfilled, and if so, switch to a new controller.</p>
<p>The controllers and the switching conditions are initialized in the <tt class="docutils literal"><span class="pre">__init__</span></tt> method of the supervisor. The following code is in place:</p>
<div class="highlight-python"><div class="highlight"><pre>def __init__(self, robot_pose, robot_info):
    """Create necessary controllers"""
    QuickBotSupervisor.__init__(self, robot_pose, robot_info)

    # Fill in poses for the controller
    self.parameters.sensor_poses = robot_info.ir_sensors.poses[:]

    # Create the controllers
    self.avoidobstacles = self.create_controller('AvoidObstacles', self.parameters)
    self.gtg = self.create_controller('GoToGoal', self.parameters)
    self.hold = self.create_controller('Hold', None)

    # Create some state transitions
    self.add_controller(self.hold)
    self.add_controller(self.gtg, \
                        (self.at_goal, self.hold), \
                        (self.at_obstacle, self.avoidobstacles))

    # Week 5 Assigment code should go here

    # End Week 5 Assignment

    # Start in 'go-to-goal' state
    self.current = self.gtg
</pre></div>
</div>
<p>This code creates three controllers - <cite>GoToGoal</cite>, <cite>AvoidObstacles</cite> and <cite>Hold</cite>. You are already familiar with the first two. The third controller just makes the robot stop (it returns (0,0) as linear and angular velocities). This code also defines a switching condition between <cite>GoToGoal</cite> and <cite>Hold</cite> and between <cite>GoToGoal</cite> and <cite>AvoidObstacles</cite>, and makes <cite>GoToGoal</cite> the starting state. The <tt class="docutils literal"><span class="pre">add_controller</span></tt> method of the supervisor should be called in the following way:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="bp">self</span><span class="o">.</span><span class="n">add_controller</span><span class="p">(</span><span class="n">controller0</span><span class="p">,</span> <span class="p">(</span><span class="n">condition1</span><span class="p">,</span> <span class="n">controller1</span><span class="p">),</span> <span class="p">(</span><span class="n">condition2</span><span class="p">,</span> <span class="n">controller2</span><span class="p">),</span> <span class="o">...</span><span class="p">)</span>
</pre></div>
</div>
<p>to add a state with a controller <tt class="docutils literal"><span class="pre">controller0</span></tt>. The conditions are functions that take no parameters and evaluate to true or false. If a condition evaluates to true, the controller is switched e.g. to <tt class="docutils literal"><span class="pre">controller1</span></tt> for <tt class="docutils literal"><span class="pre">condition1</span></tt>.</p>
<p>The code in the supervisor now corresponds to the following diagram:</p>
<img alt="_images/switching_states_incomplete.png" src="_images/switching_states_incomplete.png" />
<p>But this way the robot might never reach the goal! Your task is to update the logic to complete the diagram:</p>
<img alt="_images/switching_states.png" src="_images/switching_states.png" />
<p>You should also implement the condition functions. We suggest defining at least the following conditions:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">at_obstacle</span></tt> checks to see if any of front sensors (all but the three IR sensors in the back of the robot) detect an obstacle at a distance less than a certain limiting distance. Return <tt class="docutils literal"><span class="pre">true</span></tt> if this is the case, <tt class="docutils literal"><span class="pre">false</span></tt> otherwise.</li>
<li><tt class="docutils literal"><span class="pre">at_goal</span></tt> checks to see if the robot is within some small distance of the goal location (e.g. <tt class="docutils literal"><span class="pre">self.robot.wheels.base_length/2</span></tt>).</li>
<li><tt class="docutils literal"><span class="pre">obstacle_cleared</span></tt> checks to see if all of the front sensors report distances greater than some fixed distance. Remember, that this distance has to be larger than the distance used by <tt class="docutils literal"><span class="pre">at_obstacle</span></tt>, to avoid Zeno behaviour.</li>
</ul>
<p>When implementing various conditions, take note that the functions are called without any arguments. So, all of the parameters you want to access should be stored in the supervisor. You can precalculate anything you need in the <tt class="docutils literal"><span class="pre">process_state_info</span></tt> function that is guaranteed to be called before any conditions are checked. You may also find the following variables useful:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">self.parameters.goal.x</span></tt> (float) - The X coordinate of the goal</li>
<li><tt class="docutils literal"><span class="pre">self.parameters.goal.y</span></tt> (float) - The Y coordinate of the goal</li>
<li><tt class="docutils literal"><span class="pre">self.parameters.pose</span></tt> (<a class="reference internal" href="code_simobject.html#pose.Pose" title="pose.Pose"><tt class="xref py py-class docutils literal"><span class="pre">Pose</span></tt></a>) - The position and orientation of the robot</li>
<li><tt class="docutils literal"><span class="pre">self.parameters.velocity.v</span></tt> (float) - The given target velocity of the robot</li>
<li><tt class="docutils literal"><span class="pre">self.parameters.sensor_distances</span></tt> (list of float) - The IR distances measured by each sensor</li>
<li><tt class="docutils literal"><span class="pre">self.robot.ir_sensors.rmax</span></tt> (float) - The maximum distance that can be detected by an IR sensor</li>
<li><tt class="docutils literal"><span class="pre">self.robot.ir_sensors.poses</span></tt> (list of <a class="reference internal" href="code_simobject.html#pose.Pose" title="pose.Pose"><tt class="xref py py-class docutils literal"><span class="pre">Pose</span></tt></a>) - The positions and orientations of IR sensors in the reference frame of the robot</li>
</ul>
<div class="section" id="id11">
<h4>Testing<a class="headerlink" href="#id11" title="Permalink to this headline">¶</a></h4>
<p>You can test the the switching supervisor by running:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week5</span><span class="o">.</span><span class="n">py</span> <span class="n">switching</span>
</pre></div>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">You don&#8217;t have to restart the simulator to try another supervisor - instead you can load another world (e.g. <tt class="docutils literal"><span class="pre">week5_switching.xml</span></tt>) directly with <cite>File &gt; Open</cite>.</p>
</div>
<p>You will see two arrows showing the GoToGoal and AvoidObstacles headings, with the current heading showing as a thicker arrow:</p>
<p>The robot should successfully navigate to the same goal location (1,1) without colliding with the obstacle that is in the way. This time once the robot is near the goal, it should stop. In the log window you should see a lot of messages indicating that the controllers have been switched. You should see that the robot switches frequently between the two during its journey.</p>
</div>
</div>
<div class="section" id="mix-blending-and-switching">
<h3>Mix blending and switching<a class="headerlink" href="#mix-blending-and-switching" title="Permalink to this headline">¶</a></h3>
<p>The blending controller&#8217;s advantage is that it (hopefully) smoothly blends go-to-goal and avoid-obstacles together. However, when there are no obstacle around, it is better to purely use go-to-goal, and when the robot gets dangerously close, it is better to only use avoid-obstacles. The switching logic performs better in those kinds of situations, but jitters between go-to-goal and avoid-obstacle when close to a goal. A solution is to squeeze the blending controller in between the go-to-goal and avoid-obstacle controller.</p>
<p>To create the blending controller add the following code to the constructor in <tt class="docutils literal"><span class="pre">supervisors/week5_switching.py</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="bp">self</span><span class="o">.</span><span class="n">blending</span> <span class="o">=</span> <span class="bp">self</span><span class="o">.</span><span class="n">create_controller</span><span class="p">(</span><span class="s">&#39;week5.Blending&#39;</span><span class="p">,</span> <span class="bp">self</span><span class="o">.</span><span class="n">parameters</span><span class="p">)</span>
</pre></div>
</div>
<p>and the following code to the <tt class="docutils literal"><span class="pre">set_parameters</span></tt> method:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="bp">self</span><span class="o">.</span><span class="n">blending</span><span class="o">.</span><span class="n">set_parameters</span><span class="p">(</span><span class="bp">self</span><span class="o">.</span><span class="n">parameters</span><span class="p">)</span>
</pre></div>
</div>
<p>Implement additional conditions:</p>
<ul class="simple">
<li><tt class="docutils literal"><span class="pre">unsafe</span></tt>, that checks to see if any of the front sensors detect an obstacle closer than a critical distance (this distance should be smaller than <tt class="docutils literal"><span class="pre">at_obstacle</span></tt> critical distance).</li>
<li><tt class="docutils literal"><span class="pre">safe</span></tt>, that checks if the the minimal distance is larger than the critical distance.</li>
</ul>
<p>Those conditions can now be used to implement switching like shown on the diagram:</p>
<img alt="_images/blending_states.png" src="_images/blending_states.png" />
<div class="section" id="id12">
<h4>Testing<a class="headerlink" href="#id12" title="Permalink to this headline">¶</a></h4>
<p>You can test the switching supervisor as before. This time, the controller should switch much less often than before. Now you can also see the switches to the blended controller (blue arrow). Depending on how you set the critical distances, the number of switches and between which controllers the supervisor switches may change. Experiment with different settings to observe their effect.</p>
</div>
<div class="section" id="comparing-the-supervisor-performance">
<h4>Comparing the supervisor performance<a class="headerlink" href="#comparing-the-supervisor-performance" title="Permalink to this headline">¶</a></h4>
<p>You can make the blending and the switching supervisors race against one another:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week5</span><span class="o">.</span><span class="n">py</span> <span class="n">race</span>
</pre></div>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">You don&#8217;t have to restart the simulator to try another supervisor - instead you can load another world (e.g. <tt class="docutils literal"><span class="pre">week5_race.xml</span></tt>) directly with <cite>File &gt; Open</cite>.</p>
</div>
</div>
</div>
<div class="section" id="joystick-and-switching-optional">
<h3>Joystick and switching (optional)<a class="headerlink" href="#joystick-and-switching-optional" title="Permalink to this headline">¶</a></h3>
<p>Following Sim.I.Am, pySimiam now also has the capability to control the robot (a real or a simulated one) with a joystick. If you have a joystick, you can try it out by loading the <tt class="docutils literal"><span class="pre">joystick.xml</span></tt> world. Note, that you will need the <a class="reference external" href="http://pygame.org/download.shtml">pygame library</a> for this functionality. Also, you might want to configure your joystick in the supervisor parameter window.</p>
<p>Although controlling a robot with a joystick is fun, we can do better, since our robot is intelligent. One possible improvement will be to make the supervisor switch between the <cite>Joystick</cite> and the <cite>AvoidObstacles</cite> behaviour if the robot comes too close to an obstacle. The switching can be implemented in the same way as before, only replacing the <cite>GoToGoal</cite> controller with the <cite>Joystick</cite> controller. The supervisor code is located at <tt class="docutils literal"><span class="pre">supervisors/joystick.py</span></tt>.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">Since pySimiam supports an arbitrary number of robots, you can use more than one joystick and control more than one robot. You will have to edit <tt class="docutils literal"><span class="pre">worlds/joystick.xml</span></tt> to add more robots to the world.</p>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">The implementation of shooting robots is left to the reader as an advanced excercise.</p>
</div>
</div>

</div>
<div class="section" id="week-6-following-walls">
<h2>Week 6. Following walls<a class="headerlink" href="#week-6-following-walls" title="Permalink to this headline">¶</a></h2>
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week6</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>If you wish, you can reuse your PID code in <tt class="docutils literal"><span class="pre">controllers/pid_controller.py</span></tt> and pose estimation code in <tt class="docutils literal"><span class="pre">supervisors/quickbot.py</span></tt>.</p>
<p>This week you will be implementing a wall following behavior that will aid the robot in navigating around obstacles. Implement these parts in the <tt class="docutils literal"><span class="pre">get_heading</span></tt> method of <tt class="docutils literal"><span class="pre">controllers/week6.py</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="k">def</span> <span class="nf">get_heading</span><span class="p">(</span><span class="bp">self</span><span class="p">,</span> <span class="n">state</span><span class="p">):</span>
   <span class="sd">&quot;&quot;&quot;Get the direction away from the obstacles as a vector.&quot;&quot;&quot;</span>

   <span class="c"># Week 6 Assignment:</span>

   <span class="c"># Calculate vectors for the sensors</span>
   <span class="bp">self</span><span class="o">.</span><span class="n">vectors</span> <span class="o">=</span> <span class="p">[]</span>

   <span class="c"># Calculate the vector along the wall</span>
   <span class="bp">self</span><span class="o">.</span><span class="n">along_wall_vector</span> <span class="o">=</span> <span class="p">[</span><span class="mf">0.3</span><span class="p">,</span><span class="mi">0</span><span class="p">,</span><span class="mi">1</span><span class="p">]</span>

   <span class="c"># Calculate the vector to the closest wall point:</span>
   <span class="bp">self</span><span class="o">.</span><span class="n">to_wall_vector</span> <span class="o">=</span> <span class="p">[</span><span class="mi">0</span><span class="p">,</span><span class="mf">0.3</span><span class="p">,</span><span class="mi">1</span><span class="p">]</span>

   <span class="c"># Calculate and return the heading vector:</span>
   <span class="k">return</span> <span class="bp">self</span><span class="o">.</span><span class="n">along_wall_vector</span>

   <span class="c"># End Week 6 Assignment</span>
</pre></div>
</div>
<div class="section" id="estimate-wall-geometry">
<h3>Estimate wall geometry<a class="headerlink" href="#estimate-wall-geometry" title="Permalink to this headline">¶</a></h3>
<p>We will use the IR sensors to detect an obstacle and construct a vector that approximates a section of the obstacle (<cite>wall</cite>). In the figure, this vector, <span class="math">\(u_{fw,t}\)</span>, is illustrated in magenta.</p>
<img alt="_images/week-6-part-1.png" class="align-left" src="_images/week-6-part-1.png" />
<p>The direction of the wall following behavior (whether the obstacle on the left or right is followed) is determined by <tt class="docutils literal"><span class="pre">self.direction</span></tt>, which can either be equal to <tt class="docutils literal"><span class="pre">&quot;right&quot;</span></tt> or to <tt class="docutils literal"><span class="pre">&quot;left&quot;</span></tt>. Suppose we want to follow an obstacle to the <cite>left</cite> of the robot, then we would use the left set of IR sensors (0, 1 and 2). If we are following the wall, then at all times there should be at least one sensor that can detect the obstacle. So, we need to pick a second sensor and use the points corresponding to the measurements from these two sensors (see avoid-obstacles in Week 4) to form a line that estimates a section of the obstacle. In the figure on the left, sensors 3 and 4 are used to roughly approximate the edge of the obstacle.</p>
<img alt="_images/week-6-part-1b.png" class="align-right" src="_images/week-6-part-1b.png" />
<p>The situation is trickier when the robot reaches a corned (see the figure on the right), because typically only a single sensor will be able to detect the wall. The estimate is off as one can see in the figure, but as long as the robot isn&#8217;t following the wall too closely, it will be ok.</p>
<p>You should first fill in the <tt class="docutils literal"><span class="pre">self.vectors</span></tt> variable, as you did in week 4, to obtain the set of vectors pointing to the wall. An example strategy for estimating a section of the wall is to pick the two sensors (from IR sensors 0-2) with the smallest reported measurement in <tt class="docutils literal"><span class="pre">state.sensor_distances</span></tt>. Suppose sensor 0 and 1 returned the smallest values, then let <span class="math">\(p_1\)</span> <tt class="docutils literal"><span class="pre">=</span> <span class="pre">self.vectors[0]</span></tt> and <span class="math">\(p_2\)</span> <tt class="docutils literal"><span class="pre">=</span> <span class="pre">self.vectors[1]</span></tt>. A vector that estimates a section of the obstacle is <span class="math">\(u_{fw,t}=p_2-p_1\)</span>.</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">It is important that the sensor with larger abs(θ) (in the example, sensor 0) is assigned to <span class="math">\(p_1\)</span> and the sensor with the smaller abs(θ) (in the example, sensor 1) is assigned to <span class="math">\(p_2\)</span>, because we want that the vector points in the direction that robot should travel.</p>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">In the code, <span class="math">\(u_{fw,t}\)</span> is represented by <tt class="docutils literal"><span class="pre">self.along_wall_vector</span></tt>.</p>
</div>
<p>The figures correspond to the above example strategy, but you may want to experiment with different strategies for computing <span class="math">\(u_{fw,t}\)</span>. A better estimate would make wall following safer and smoother when the robot navigates around the corners of obstacles.</p>
</div>
<div class="section" id="find-the-closest-wall-point">
<h3>Find the closest wall point<a class="headerlink" href="#find-the-closest-wall-point" title="Permalink to this headline">¶</a></h3>
<p>Now that we have the vector <span class="math">\(u_{fw,t}\)</span> (represented by the magenta arrow in the figures), we need to compute a vector <span class="math">\(u_{fw,p}\)</span> that points from the robot to the closest point on <span class="math">\(u_{fw,t}\)</span>. This vector is visualized as blue arrow in the figures and can be computed using a little bit of linear algebra:</p>
<div class="math">
\[\begin{split}\begin{split}
   u'_{fw,t} &amp;= \frac{u_{fw,t}}{\|u_{fw,t}\|}, \quad u_p = \begin{bmatrix} x \\ y \end{bmatrix}, \quad u_a = p_1 \\
   u_{fw,p} &amp;= (u_a-u_p)-((u_a-u_p)\cdot u'_{fw,t})u'_{fw,t}
\end{split}\end{split}\]</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">A small technicality is that we are computing <span class="math">\(u_{fw,p}\)</span> as the the vector pointing from the robot to the closest point on <span class="math">\(u_{fw,t}\)</span>, as if <span class="math">\(u_{fw,t}\)</span> were infinitely long.</p>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">In the code, <span class="math">\(u_{fw,p}\)</span> is represented by <tt class="docutils literal"><span class="pre">self.to_wall_vector</span></tt>.</p>
</div>
</div>
<div class="section" id="compute-the-heading-vector">
<h3>Compute the heading vector<a class="headerlink" href="#compute-the-heading-vector" title="Permalink to this headline">¶</a></h3>
<p>The last step is to combine <span class="math">\(u_{fw,t}\)</span> and <span class="math">\(u_{fw,p}\)</span> such that the robot follows the obstacle all the way around at some distance <span class="math">\(d_{fw}\)</span> (<tt class="docutils literal"><span class="pre">self.distance</span></tt> in the code). <span class="math">\(u_{fw,t}\)</span> will ensure that the robot drives in a direction that is parallel to an edge on the obstacle, while <span class="math">\(u_{fw,p}\)</span> needs to be used to maintain a distance <span class="math">\(d_{fw}\)</span> from the obstacle.</p>
<p>One way to achieve this is,</p>
<div class="math">
\[u'_{fw,p} = u_{fw,p}-d_{fw}\frac{u_{fw,p}}{\|u_{fw,p}|},\]</div>
<p>where <span class="math">\(u'_{fw,p}\)</span> is now a vector points towards the obstacle when the distance to the obstacle, <span class="math">\(d&gt;d_{fw}\)</span>, is near zero when the robot is <span class="math">\(d_{fw}\)</span> away from the obstacle, and points away from the obstacle when <span class="math">\(d&lt;d_{fw}\)</span>.</p>
<p>All that is left is to linearly combine <span class="math">\(u'_{fw,t}\)</span> and <span class="math">\(u'_{fw,p}\)</span> into a single vector <span class="math">\(u_{fw}\)</span> that can be used with the PID controller to steer the robot along the obstacle at the distance <span class="math">\(d_{fw}\)</span>. (<cite>Hint</cite>: Think about how this worked with <span class="math">\(u_{ao}\)</span> and <span class="math">\(u_{gtg}\)</span> last week).</p>
</div>
<div class="section" id="id14">
<h3>Testing<a class="headerlink" href="#id14" title="Permalink to this headline">¶</a></h3>
<p>Running <tt class="docutils literal"><span class="pre">qtsimiam_week6.py</span></tt> shows you a world with six robots and two obstacles. The robots are set up near the obstacle, so that they can start following it immediately. This is a valid situation, because we are assuming another behavior (like go-to-goal) has brought us near the obstacle.</p>
<p>First, test the construction of <tt class="docutils literal"><span class="pre">to_wall_vector</span></tt> and <tt class="docutils literal"><span class="pre">along_wall_vector</span></tt>. Do not start the simulation yet. For each robot you should see the two vectors positioned correctly -  the magenta arrow approximately matches up with the edge of the obstacle, and the blue arrow should point from the robot to the closest point on the wall.</p>
<p>Second, test the follow wall behaviour by running the simulation. The robots should be able to follow the obstacle all the way around. Set <cite>distance</cite> to some distance in [0.04, 0.3] m. The robot should follow the wall at approximately the specified distance. If the robot does not follow the wall at the specified distance, then <span class="math">\(u'_{fw,p}\)</span> is not given enough weight (or <span class="math">\(u'_{fw,t}\)</span> is given too much weight).</p>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">Depending on how the edges of the obstacle are approximated, it is possible for the robot to peel off at one of the corners. This is not the case in the example strategy provided for the first part.</p>
</div>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">If the amount of robots seems overwhelming, you can comment out some of them in the <tt class="docutils literal"><span class="pre">worlds/week6.xml</span></tt>. If the simulation is too slow, turn off drawing of robot trajectories.</p>
</div>
</div>

</div>
<div class="section" id="controlling-the-real-quickbot">
<h2>Controlling the real QuickBot<a class="headerlink" href="#controlling-the-real-quickbot" title="Permalink to this headline">¶</a></h2>
<p>If you have built a QuickBot, you can use pySimiam and the controllers/supervisors you implemented to make it autonomous.</p>
<div class="section" id="establishing-the-connection">
<h3>Establishing the connection<a class="headerlink" href="#establishing-the-connection" title="Permalink to this headline">¶</a></h3>
<p>First, you have to make sure that pySimiam and the robot can communicate with each other. Start by following the <a class="reference external" href="https://class.coursera.org/conrob-002/wiki/Hardware">instructions</a> provided by Rowland O&#8217;Flaherty to find out the IP addresses of you host computer and the robot, and to start the program on the robot. After this is done, edit the <tt class="docutils literal"><span class="pre">worlds/qb_realtime_pc.xml</span></tt> world file:</p>
<div class="highlight-python"><pre>&lt;?xml version="1.0" ?&gt;
&lt;simulation&gt;
    &lt;robot type="qb_realtime.QuickBot" options='{"baseIP":"192.168.0.1", "robotIP":"192.168.0.6", "port":5005}'&gt;
        &lt;pose theta="0.0" x="0.0" y="0.0"/&gt;
        &lt;supervisor type="qb_realtime_pwmtest.PWMTest"/&gt;
    &lt;/robot&gt;
&lt;/simulation&gt;</pre>
</div>
<p>You have to set <em>baseIP</em> to your host IP address, <em>robotIP</em> to your robot IP address, and <em>port</em> to the port you chose earlier. Now, you can run the control code:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_realtime</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>If there is no error message after a couple of seconds, the connection with the QuickBot has been established successfully.</p>
</div>
<div class="section" id="calibrating-the-motors">
<h3>Calibrating the motors<a class="headerlink" href="#calibrating-the-motors" title="Permalink to this headline">¶</a></h3>
<p>The second step is the calibration of the motors. The angular velocity of the wheels is defined by the <a class="reference external" href="http://en.wikipedia.org/wiki/Pulse-width_modulation">pulse-width-modulated signal</a> (PWM) that the BeagleBone board is sending to the motors. This dependence is not known apriori, as it depends on the motors, the wheels and the surface. To be able to control your robot reliably, you have to measure this dependence and put into code.</p>
<img alt="_images/pwm2v.png" class="align-left" src="_images/pwm2v.png" style="width: 400px;" />
<p>To simplify the task, we are going to assume a dependence in the form shown on the graph: there is a minimal PWM number required to make the wheels turn, and after this point the angular velocity increases linearly with the power provided.</p>
<p>When you start the program, the supervisor that you get allows you to control the PWM for left and right wheel separately. Begin by determining the lowest PWM setting for the robot to start moving. Try several values (e.g. 25, 50 and 75) for a rough estimate and then fine-tune the value until you have reached the minimum velocity. Measure the linear speed of the robot, with both wheels at this setting. You can now calculate the angular velocity using the formula from Week 1. Next, set both wheels to a high PWM value (70-90) and measure the speed again. Calculate the angular velocity again.</p>
<p>You have now four numbers - PWM and angular velocity in the minimum (<tt class="docutils literal"><span class="pre">pwm_min</span></tt> and <tt class="docutils literal"><span class="pre">vel_min</span></tt>) and PWM and angular velocity in the maximum (<tt class="docutils literal"><span class="pre">pwm_max</span></tt> and <tt class="docutils literal"><span class="pre">vel_max</span></tt>). Around line 32 in <tt class="docutils literal"><span class="pre">robots/qb_realtime.py</span></tt> you will find the variable <tt class="docutils literal"><span class="pre">beta</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="n">beta</span> <span class="o">=</span> <span class="p">(</span><span class="mf">1.0</span><span class="p">,</span> <span class="mf">0.0</span><span class="p">)</span>
</pre></div>
</div>
<p>This variable is used to convert from angilar velocities to PWM values and back. You should set it in such a way that</p>
<div class="math">
\[\begin{split}v_\mathrm{min} &amp;= \beta_0 \mathrm{PWM}_\mathrm{min} + \beta_1 \\
v_\mathrm{max} &amp;= \beta_0 \mathrm{PWM}_\mathrm{max} + \beta_1\end{split}\]</div>
<p>Around line 144 you will also find the limits of angular velocity that are used in <tt class="docutils literal"><span class="pre">ensure_w</span></tt>:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="bp">self</span><span class="o">.</span><span class="n">info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">min_velocity</span> <span class="o">=</span> <span class="mi">2</span><span class="o">*</span><span class="n">pi</span><span class="o">*</span><span class="mi">30</span><span class="o">/</span><span class="mi">60</span>  <span class="c">#  30 RPM</span>
<span class="bp">self</span><span class="o">.</span><span class="n">info</span><span class="o">.</span><span class="n">wheels</span><span class="o">.</span><span class="n">max_velocity</span> <span class="o">=</span> <span class="mi">2</span><span class="o">*</span><span class="n">pi</span><span class="o">*</span><span class="mi">130</span><span class="o">/</span><span class="mi">60</span> <span class="c"># 130 RPM</span>
</pre></div>
</div>
<p>Set those to <tt class="docutils literal"><span class="pre">vel_min</span></tt> and <tt class="docutils literal"><span class="pre">vel_max</span></tt>, respectively.</p>
</div>
<div class="section" id="running-the-robot">
<h3>Running the robot<a class="headerlink" href="#running-the-robot" title="Permalink to this headline">¶</a></h3>
<p>Congratulations! You are as good as done. The only thing left to change is the supervisor in <tt class="docutils literal"><span class="pre">worlds/qb_realtime_pc.xml</span></tt>. Change the following:</p>
<div class="highlight-python"><pre>&lt;supervisor type="qb_realtime_pwmtest.PWMTest"/&gt;</pre>
</div>
<p>to, for example:</p>
<div class="highlight-python"><pre>&lt;supervisor type="week6.QBWallSupervisor"/&gt;</pre>
</div>
<p>to have your robot follow the walls. Now reopen the world, press the &#8216;play&#8217; button and watch your robot move.</p>
</div>
</div>
<div class="section" id="week-7-bringing-it-all-together">
<h2>Week 7. Bringing it all together<a class="headerlink" href="#week-7-bringing-it-all-together" title="Permalink to this headline">¶</a></h2>
<p>The simulator for this week can be run with:</p>
<div class="highlight-python"><div class="highlight"><pre><span class="gp">&gt;&gt;&gt; </span><span class="n">python</span> <span class="n">qtsimiam_week7</span><span class="o">.</span><span class="n">py</span>
</pre></div>
</div>
<p>You are encouraged (but not required) to reuse your code from week 6, by using your version of the follow-wall controller in <tt class="docutils literal"><span class="pre">controllers/followwall.py</span></tt>. You can also reuse parts of your state machine from week 5.</p>
<p>This week you will be combining the go-to-goal, avoid-obstacles, and follow-wall controllers into a full navigation system for the robot. The robot will be able to navigate around a cluttered, complex environment without colliding with any obstacles and reaching the goal location successfully. Implement your solution in <tt class="docutils literal"><span class="pre">supervisors/week7.py</span></tt>.</p>
<p>By default, the robot is set up to switch between <em>AvoidObstacles</em> and <em>GoToGoal</em> to navigate the environment. However, if you launch the simulator with this default behavior, you will notice that the robot cannot escape the larger obstacle as it tries to reach the goal located at (1.1,1.1). The robot needs a better strategy for navigation. Instead of just turning away from obstacles, it can follow the obstacle using the <em>FollowWall</em> controller from the last week. At some point, however, the robot should detach itself from the wall and go straight for the goal again. There are two conditions that determine this detachment point.</p>
<div class="section" id="finding-out-if-any-progress-is-being-made">
<h3>Finding out if any progress is being made<a class="headerlink" href="#finding-out-if-any-progress-is-being-made" title="Permalink to this headline">¶</a></h3>
<p>The <tt class="docutils literal"><span class="pre">progress_made</span></tt> condition determines whether the robot is making any progress towards the goal. Implement the function <tt class="docutils literal"><span class="pre">progress_made</span></tt> such that it returns <tt class="docutils literal"><span class="pre">True</span></tt> if</p>
<div class="math">
\[\begin{split}\left\|\begin{bmatrix} x-x_g \\ y-y_g \end{bmatrix}\right\| &lt; d_{\text{progress}}-\epsilon,\end{split}\]</div>
<p>where ε = 0.1 gives a little bit of slack, and <span class="math">\(d_{\text{progress}}\)</span> is the closest (in terms of distance) the robot has progressed towards the goal. This distance can be set before switching to the <em>FollowWall</em> behaviour in the <tt class="docutils literal"><span class="pre">at_obstacle</span></tt> condition.</p>
</div>
<div class="section" id="finding-out-if-going-straight-for-the-goal-makes-sense">
<h3>Finding out if going straight for the goal makes sense<a class="headerlink" href="#finding-out-if-going-straight-for-the-goal-makes-sense" title="Permalink to this headline">¶</a></h3>
<p>The <tt class="docutils literal"><span class="pre">can_detach</span></tt> condition determines whether going straight for the goal would bring the robot further away from the obstacles. Implement the function <tt class="docutils literal"><span class="pre">can_detach</span></tt> such that it returns <tt class="docutils literal"><span class="pre">True</span></tt> if the vector towards the goal is pointing away from the wall. In other words, the robot should detach from the wall on the left if <span class="math">\(u_gtg \times u_fw &gt; 0\)</span>, and from the wall on the right if <span class="math">\(u_gtg \times u_fw &lt; 0\)</span>.</p>
</div>
<div class="section" id="switching">
<h3>Switching<a class="headerlink" href="#switching" title="Permalink to this headline">¶</a></h3>
<p>Now, we are ready to implement a finite state machine (FSM) that solves the full navigation problem. As already seen in Week 5, a finite state machine is nothing but a set of states (controllers) and switching conditions, that first check which state (or behavior) the robot is in, then based on whether a condition is satisfied, the FSM switches to another state or stays in the same state. Some of the logic that should be part of the FSM is:</p>
<blockquote>
<div><ol class="arabic simple">
<li>If <tt class="docutils literal"><span class="pre">at_goal</span></tt>, then switch to <em>Hold</em>.</li>
<li>If <tt class="docutils literal"><span class="pre">unsafe</span></tt>, then switch to <em>AvoidObstacles</em>.</li>
<li>If in state <em>GoToGoal</em> and <tt class="docutils literal"><span class="pre">at_obstacle</span></tt> and not <tt class="docutils literal"><span class="pre">can_detach</span></tt>, then check whether the robot needs to follow the wall on the left or on the right and set <tt class="docutils literal"><span class="pre">self.parameters.direction</span></tt> and <span class="math">\(d_{\text{progress}}\)</span>  (the best place to do so is inside the <tt class="docutils literal"><span class="pre">at_obstacle</span></tt> condition if it evaluates to <tt class="docutils literal"><span class="pre">True</span></tt>). Then switch to state <em>FollowWall</em>.</li>
<li>If in state <em>FollowWall</em>, check whether <tt class="docutils literal"><span class="pre">progress_made</span></tt> and <tt class="docutils literal"><span class="pre">can_detach</span></tt> are both true. If so, switch to state <em>GoToGoal</em>, otherwise keep following the wall.</li>
</ol>
</div></blockquote>
</div>
<div class="section" id="id16">
<h3>Testing<a class="headerlink" href="#id16" title="Permalink to this headline">¶</a></h3>
<p>To test your code, the simulator is set up to run a simple FSM that is unable to exit the large obstacle and advance towards the goal.</p>
<p>Testing the full navigation systems is mostly a binary test: does the robot successfully reach the goal located at (1.1,1.1) or not? However, let us consider a few key situations that will likely be problematic.</p>
<blockquote>
<div><ol class="arabic simple">
<li>First, the default code has the problem that the robot is stuck inside the large obstacle. The reason for this situation is that avoid obstacle is not enough to push the robot far enough way from the obstacle, such that when go-to-goal kicks back in, the robot is clear of the obstacle and has a free path towards the goal. This is solved by using <em>FollowWall</em> instead of <em>AvoidObstacles</em> when close to an obstacle.</li>
<li>Second, assuming that the robot has escaped the interior of the large obstacle and is in wall following mode, there is a point at which progress is again being made towards the goal and folloing the wall is no longer necessary. The robot should then stop wall following and resume its go-to-goal behavior. A common problem is that the robot either continues to follow the edge of the large obstacle and never makes the switch to go-to-goal. Another common problem is that the FSM switches to the go-to-goal behavior before the robot has the chance to escape the interior of the large obstacle using wall following. Troubleshoot either problem by revisiting the logic that uses the <tt class="docutils literal"><span class="pre">progress_made</span></tt> and <tt class="docutils literal"><span class="pre">can_detach</span></tt> conditions to transition from <tt class="docutils literal"><span class="pre">FollowWall</span></tt> to <tt class="docutils literal"><span class="pre">GoToGoal</span></tt>.</li>
</ol>
</div></blockquote>
<div class="admonition note">
<p class="first admonition-title">Note</p>
<p class="last">Remember that adding <tt class="docutils literal"><span class="pre">print</span></tt> calls to different parts of your code can help you debug your problems. By default, the supervisor prints out the state that it switches to.</p>
</div>
</div>

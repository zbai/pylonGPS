/**
\mainpage
Introduction
---------------------
_______________

Hello and welcome.

We are just starting to see the deployment of robots in a commercial setting and most of the pieces are in place for Robotics as a Service. This project is dedicated to making it even easier to do interesting and useful robotics applications using inexpensive differential GPS.

Differential GPS gives enhanced accuracy (<10 cm radius vs the normal 3000 cm radius) which can enable applications such as landing a quadcopter on a small platform or keeping a mobile robot on the sidewalk. It works by having a nearby GPS basestation with a known location that can tell the mobile unit how to compensate for the errors that the basestation has observed in the GPS signal.

Pylon GPS makes it easy to share GPS updates from your basestation and allows mobile units to get updates from any nearby basestations. This means that when a basestation with Pylon GPS is deployed, everyone within 10 km of the basestation can get updates and create applications using differential GPS.  The PylonGPS library allows anyone to setup a basestation, caster or read from a basestation, as well as setup proxy casters and search for good basestations with SQL like queries.

By default, the transceiver GUI points to the caster at pylongps.com.  PylonGPS allows a caster to be scaled to an arbitrary size, which means that everyone can use one caster and have all basestations available to everyone.  Adding support in the transceiver GUI for different casters is possible with some work, so please contact the author (crwest@ncsu.edu) if your use case is incompatible with everyone having access via pylongps.com.


Compilation
---------------------
_______________


The next few minor releases will focus on making it easier to install the software by providing Debian packages and Windows installers.  For now, the preferred method is building from source.  So far, building and running has been tested on Ubuntu Linux (15.10) and the instructions focus on that accordingly.

The PylonGPS source can be downloaded via: <br>
https://github.com/charlesrwest/pylonGPS/archive/master.zip

Alternatively, it can be cloned from GitHub using the following git command:<br>
git clone https://github.com/charlesrwest/pylonGPS.git

<b>Required libraries/utilities:</b><br>
<ul>
<li> G++ with support for C++11 (most systems support this)
<li> CMake (http://www.cmake.org/)
<li> Protobuf (https://developers.google.com/protocol-buffers/)
<li> ZeroMQ (http://zeromq.org/)
<li> POCO (http://pocoproject.org/)
<li> SQLITE3 (https://www.sqlite.org/)
<li> Sodium (https://download.libsodium.org/doc/)
</ul>

<b>Required if documentation is desired:</b>
<ul>
<li> Doxygen (http://www.stack.nl/~dimitri/doxygen/)
</ul>

<b>Required if GUIs are desired:</b>
<ul>
<li> Qt5 (Widgets, Svg modules: http://www.qt.io/developers/)
<li> Marble (library, compiled for Qt5: https://marble.kde.org/dev-intro.php)
</ul>

<b>Embedded Libraries:</b>
<ul>
<li> ZeroMQ's header only C++ extension (https://github.com/zeromq/cppzmq)
<li> Catch, a header only unit test framework (https://github.com/philsquared/Catch)
<li> JsonCPP, a Json serialization/deserialization library (https://github.com/open-source-parsers/jsoncpp)
</ul>

On Ubuntu Linux, it should be possible to install all required dependencies with the following command:

<b>#REQUIRED</b>
<br>
sudo apt-get install build-essential cmake protobuf-compiler libprotobuf-dev libzmq3-dev libpoco-dev libsodium-dev libsqlite3-dev

<b>#FOR DOCUMENTATION COMPILATION</b>
<br>
sudo apt-get install doxygen

<b>#FOR GUIs</b>
<br>
sudo apt-get install libmarble-dev qtbase5-dev libqt5svg5-dev

Compilation can be carried out via the following commands performed in the downloaded PylonGPS directory:

<b>#Compile just the library and the command line programs</b> <br>
cmake ./ <br>
make

<b>#Compile the documentation</b> <br>
cmake ./ -DBUILD_DOCS=ON <br>
make doc

<b>#Compile library, command line programs and GUIs</b> <br>
cmake ./  -DBUILD_GUIS=ON <br>
make

If the documentation is compiled, it generates html files which allow browsing the code documentation in a web browser via the /pylonGPS/doc/html/index.html file (just double click on the file and it should open a browser).  The linkToGeneratedDocumentation.html file has been added to the top level directory to make it easier to get the the generated index file.

The integrity of the code can be checked via running the ./bin/unitTests executable.  If some of the unit tests fail on your platform, please email crwest@ncsu.edu with a screenshot of your error and a description of your operating enviroment.

Using PylonGPS
---------------------
_______________

Without the GUIs enabled, PylonGPS currently generates 3 executables, one shared library and one static library. One of the executables is meant to unit test the code and will probably not be used by most people.  The static library is integrated into the shared library and isn't really used outside of the build process.

Command line programs with options will display possible options if the "-help" option is used:

./bin/program -help

<b>./lib/libpylongps.so:</b><br>
This shared library includes most of the functionality in the PylonGPS software and is linked to by all of the executables.

<b>./bin/caster:</b> <br>
This is a command line version of the Pylon GPS caster.  Starting it without any arguments will create a caster that will share any community basestations with whoever connects to it.  Alternatively, it can be given a configuration file generated by the casterGUI which can allow different port numbers to be used and enable one or more trusted signers to be added.

<b>./bin/testDataSender:</b> <br>
This program makes two dummy basestations in Raleigh, NC which just repeat strings.  It will be removed soon, as it was only meant to assist with debugging.

With the GUIs enabled, the following are also generated:

<b>./bin/casterGUI:</b> <br>
This GUI allows a configuration file for a caster to generated, keys for basestations to be created/signed and signing keys to be added to/removed from a running caster.

To setup a caster with custom settings (if you aren't using the pylongps.com one), do the following:

1. Open the caster GUI
2. Use the "Generate Key Pair" button twice to generate two pairs of key files (one pair for caster authentication, one for using the key management interface later)
3. Select the keys that were generated in the "Configure Caster" tab.
4. If you are happy with your caster settings, use the "Save Caster Configuration" button and save the generated file.
5.  Open the caster program with the option "-C thePathToTheSavedConfigurationFile"

The casterGUI can be used to create a credentials file for an authenticated basestation as follows:

1. Press the "Create Credentials" Button to go to the tab
2. Select the basestation public key file (created by the "Generate Key Pair" interface) to create the credentials file for.
3. Enter how many basestations the key can be used for at the same time and when the credentials should expire.
4. Select any key pairs which will grant the permissions (private key, public key, alternating).
5. Press "Create Credentials" and select where to save the credentials file.

The casterGUI can also be used to add or remove recognized signers from a running caster as follows:

1. Press the "Add/Remove Keys" button to go to the tab.
2. Enter the IP address and port used for key management with the caster to modify.
3. Select the key management key pair that was used in originally setting up the caster. 
4. Select a public key to add/remove in the correct frame depending on which category to place it in (registered_community, official or blacklisted).
5. Select how long the change will be valid (when a signing key expires or after the key to get rid of expires).
6. Press the button associated with the change type to make it take effect.

<b>./bin/transceiverGUI:</b><br>
This GUI allows for data sources from files, TCP servers, ZMQ publishers and PylonGPS casters to be forwarded to files, PylonGPS casters/hosted on a local TCP server or published by a ZMQ publisher.  It also allows the PylonGPS basestations to be view on a world map.

On startup, the map should zoom to the area you are in using your IP address to figure out the location.  If that doesn't work, you should be able to enter your address in the top left and hit "Find" to go to the right location.  You can also left click and drag to move on the map and use the mouse wheel to adjust zoom.  All available basestations should be shown below the "Find" frame, sorted from their distance from the center of the current view (which should by distance from the address of interest).

Details associated with a basestation are displayed displayed if the mouse is hovered over them or the basestation is clicked on in the map.  The basestation can be selected as a data source by clicking the "+" button on it's details widget.  Upon selection, it will be copied to the right side of the window (where it will remain unless removed even if the associated basestation shuts down).

Alternate data sources can be selected by pressing the "Create New Source" button, which opens a dialog window.  Data can be received using the dialog from files, a TCP server or a ZMQ publisher.  Once created, the source will appear on the right side of the screeen.

Any data source can be removed by pressing the "-" button on the left side of the associated widget.  This will remove any associated data senders as well.

Once the data sources have been selected, press the "Manage Senders" button on the bottom right to go to the menu to select where to forward the received data.  To go back, just press the "Manage Receivers" button on the bottom right part of the menu.

Pressing the "+" button on the data sources will open a dialog menu to create a data sender.  You can forward the data source's updates to a file, create a TCP server which sends to everyone who connects to it, create a ZMQ publisher which publishes the data to all subscribers or forward the data to a PylonGPS caster.  Upon creation of a sender, it will appear on the right side of the menu with a black line connecting it to the associated data source.  Any number of data senders can be created, but each can only have one data source.

A community data sender can be made by entering it's location, message format and expected update rate.  A registered community or official basestation needs that information as well as a key pair and credentials file signed by a recognized authority. Once the basestation is created, it will appear on the map within seconds (might need to move the map to force an update). Likewise, a basestation will be removed from the map within seconds of being shutdown.

The current set of data sources/senders can be saved as a configuration file and retrieved using the "Save Configuration" and "Load Configuration" buttons in the bottom left.

Future Updates
---------------------
_______________


It is likely that users will want a command line version of the transceiver GUI so that it can be run in the background or in enviroments which don't support QT5.  A minimumal version which can load from a configuration file would be simple to make.  A stand alone version would take longer (email the author if your use case requires it: crwest@ncsu.edu).

It may also be possible to add an NTRIP 1.0 option to the transceiver (email the author if your use case requires it: crwest@ncsu.edu).

With some work, the transceiver GUI could also have the capability to connect to other PylonGPS casters or mutiple at the same time (email the author if your use case requires it: crwest@ncsu.edu).
*/

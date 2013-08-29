#include "ofApp.h"

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::setup()
{
	isServer = false;
	//ofSetFrameRate(24);
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
		
	ofSeedRandom();
	int uniqueID = ofRandom( 999999999 ); // Yeah this is bogus I know. Good enough for our purposes.
    server = NULL;
	client = NULL;
	
    if( ofFile( ofToDataPath("Settings/IsServer.txt")).exists() )
	{
		server = new ServerOscManager();
		server->init( "Settings/ServerSettings.xml" );
        
		isServer = server->isInitialised();
        cout<<"Starting Server"<<endl;
	}
	else
	{
		client = new ClientOSCManager();
		client->init( uniqueID );
		
		commonTimeOsc = client->getCommonTimeOscObj();
		commonTimeOsc->setEaseOffset( true );
		
		ofAddListener( client->newDataEvent, this, &ofApp::newData );
        
        cout<<"Starting Client"<<endl;
	}
    
    // Read the screen index from a file
	ofxXmlSettings XML;
	bool loadedFile = XML.loadFile( "Settings/ClientSettings.xml" );
	if( loadedFile )
	{
		        
	}
    
    mPlayer.loadMovie("movies/fingers.mov");
	mPlayer.play();
    framebyframe = false;

}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::update()
{
    currTime = 0.0f;
    if( isServer ) { currTime = ofGetElapsedTimef(); } else { currTime = commonTimeOsc->getTimeSecs(); }
    mPlayer.update();
    if(!framebyframe){
        float temp = ofMap(sin(currTime/mPlayer.getDuration()), -1, 1, 0, 1);
        mPlayer.setPosition(temp);
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::draw()
{

	mPlayer.draw(0, 0);
	
    if( isServer )
    {
        fontSmall.drawString( "Server", 300, 85 );
    }
    else
    {
        fontSmall.drawString( "Time: " + ofToString(currTime), 100, 160);
        fontSmall.drawString( "Offset: " + ofToString(commonTimeOsc->offsetMillis) + " OffsetTarget: " + ofToString(commonTimeOsc->offsetMillisTarget), 100, 80 );
    }
	
}

void ofApp::newData( DataPacket& _packet  )
    {
        if(!isServer){
            if(framebyframe)
                mPlayer.nextFrame();
        }
    }

    
    
// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::keyPressed(int key)
{
    if(key == ' '){
        framebyframe = !framebyframe;
        mPlayer.setPaused(framebyframe);
    }
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::keyReleased(int key)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::mouseMoved(int x, int y )
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::mouseDragged(int x, int y, int button)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::mousePressed(int x, int y, int button)
{
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
//
void ofApp::mouseReleased(int x, int y, int button)
{
}

/****************************************************************************

  example3.cpp

  A GLUT program using all the features of the GLUI User Interface Library
  (except columns, featured in example4.cpp)

  -----------------------------------------------------------------------
	   
  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

#include <string.h>
#include <GL/glui.h>

float xy_aspect;
int   last_x, last_y;
float rotationX = 0.0, rotationY = 0.0;

/** These are the live variables passed into GLUI ***/
int   wireframe = 0;
int   obj_type = 1;
int   segments = 8;
int   segments2 = 8;
std::string text = "Hello World!";
int   light0_enabled = 1;
int   light1_enabled = 0;
float light0_intensity = 1.0;
float light1_intensity = 1.0;
int   main_window;
int   counter = 0;
float scale = 1.0;

/** Pointers to the windows and some of the controls we'll create **/
GLUI *cmd_line_glui=0, *glui;
GLUI_Checkbox    *checkbox;
GLUI_Spinner     *spinner, *light0_spinner, *light1_spinner, *scale_spinner;
GLUI_RadioGroup  *radio;
GLUI_EditText    *edittext;
GLUI_CommandLine *cmd_line;
GLUI_Panel       *obj_panel;
GLUI_Button      *open_console_btn;

/********** User IDs for callbacks ********/
#define OPEN_CONSOLE_ID      100
#define CMD_HIST_RESET_ID    101
#define CMD_CLOSE_ID         102
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  251

/********** Miscellaneous global variables **********/

GLfloat light0_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light0_diffuse[] =  {.6f, .6f, 1.0f, 1.0f};
GLfloat light0_position[] = {.5f, .5f, 1.0f, 0.0f};

GLfloat light1_ambient[] =  {0.1f, 0.1f, 0.3f, 1.0f};
GLfloat light1_diffuse[] =  {.9f, .6f, 0.0f, 1.0f};
GLfloat light1_position[] = {-1.0f, -1.0f, 1.0f, 0.0f};

/**************************************** control_cb() *******************/
/* GLUI control callback                                                 */

void control_cb( int control )
{
  if ( control == LIGHT0_ENABLED_ID ) {
    if ( light0_enabled ) {
      glEnable( GL_LIGHT0 );
      light0_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT0 ); 
      light0_spinner->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED_ID ) {
    if ( light1_enabled ) {
      glEnable( GL_LIGHT1 );
      light1_spinner->enable();
    }
    else {
      glDisable( GL_LIGHT1 ); 
      light1_spinner->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY_ID ) {
    float v[] = { light0_diffuse[0],  light0_diffuse[1],
		  light0_diffuse[2],  light0_diffuse[3] };
    
    v[0] *= light0_intensity;
    v[1] *= light0_intensity;
    v[2] *= light0_intensity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY_ID ) {
    float v[] = { light1_diffuse[0],  light1_diffuse[1],
		  light1_diffuse[2],  light1_diffuse[3] };
    
    v[0] *= light1_intensity;
    v[1] *= light1_intensity;
    v[2] *= light1_intensity;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
}

/**************************************** pointer_cb() *******************/
/* GLUI control pointer callback                                         */
/* You can also use a function that takes a GLUI_Control pointer  as its */
/* argument.  This can simplify things sometimes, and reduce the clutter */
/* of global variables by giving you the control pointer directly.       */
/* For instance here we didn't need an additional global ID for the      */
/* cmd_line because we can just compare pointers directly.               */

void pointer_cb( GLUI_Control* control )
{
  if (control->get_id() == OPEN_CONSOLE_ID ) {
    /****** Make command line window ******/
    cmd_line_glui = GLUI_Master.create_glui( "Enter command:",
      0, 50, 500 );
    
    cmd_line = new GLUI_CommandLine( 
      cmd_line_glui, "Command (try 'exit'):", NULL, -1, pointer_cb );
    cmd_line->set_w( 400 );  /** Widen 'command line' control **/

    GLUI_Panel *panel = new GLUI_Panel(cmd_line_glui,"", GLUI_PANEL_NONE);
    new GLUI_Button(panel, "Clear History", CMD_HIST_RESET_ID, pointer_cb);
    new GLUI_Column(panel, false);
    new GLUI_Button(panel, "Close", CMD_CLOSE_ID, pointer_cb);
    
    cmd_line_glui->set_main_gfx_window( main_window );

    control->disable();
  }
  else if ( control->get_id() == CMD_CLOSE_ID ) {
    open_console_btn->enable();
    control->glui->close();
  }
  else if ( control == cmd_line ) {
    /*** User typed text into the 'command line' window ***/
    printf( "Command (%d): %s\n", counter, cmd_line->get_text() );
    std::string text = cmd_line->get_text();
    if (text =="exit" || text == "quit")
      exit(0);
  }
  else if ( control->get_id() == CMD_HIST_RESET_ID ) {
    cmd_line->reset_history();
  }

}

/**************************************** myGlutKeyboard() **********/

void myGlutKeyboard(unsigned char Key, int x, int y)
{
  switch(Key)
  {
    // A few keys here to test the sync_live capability.
  case 'o':
    // Cycle through object types
    ++obj_type %= 3;
    GLUI_Master.sync_live_all();
    break;
  case 'w':
    // Toggle wireframe mode
    wireframe = !wireframe;
    GLUI_Master.sync_live_all();
    break;
  case 27: 
  case 'q':
    exit(0);
    break;
  };
  
  glutPostRedisplay();
}


/***************************************** myGlutMenu() ***********/

void myGlutMenu( int value )
{
  myGlutKeyboard( value, 0, 0 );
}


/***************************************** myGlutIdle() ***********/

void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  


  glutPostRedisplay();

  /****************************************************************/
  /*            This demonstrates GLUI::sync_live()               */
  /*   We change the value of a variable that is 'live' to some   */
  /*   control.  We then call sync_live, and the control          */
  /*   associated with that variable is automatically updated     */
  /*   with the new value.  This frees the programmer from having */
  /*   to always remember which variables are used by controls -  */
  /*   simply change whatever variables are necessary, then sync  */
  /*   the live ones all at once with a single call to sync_live  */
  /****************************************************************/

  counter++;
   
  glui->sync_live();

}

/***************************************** myGlutMouse() **********/

void myGlutMouse(int button, int button_state, int x, int y )
{
  if ( button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN ) {
    last_x = x;
    last_y = y;
  }
}


/***************************************** myGlutMotion() **********/

void myGlutMotion(int x, int y )
{
  rotationX += (float) (y - last_y);
  rotationY += (float) (x - last_x);

  last_x = x;
  last_y = y;

  glutPostRedisplay(); 
}

/**************************************** myGlutReshape() *************/

void myGlutReshape( int x, int y )
{
  xy_aspect = (float)x / (float)y;
  glViewport( 0, 0, x, y );

  glutPostRedisplay();
}

/***************************************** myGlutDisplay() *****************/

void myGlutDisplay( void )
{
  glClearColor( .9f, .9f, .9f, 1.0f );
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  glFrustum( -xy_aspect*.08, xy_aspect*.08, -.08, .08, .1, 15.0 );

  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glTranslatef( 0.0, 0.0, -1.2f );
  glRotatef( rotationY, 0.0, 1.0, 0.0 );
  glRotatef( rotationX, 1.0, 0.0, 0.0 );

  glScalef( scale, scale, scale );

  /*** Now we render object, using the variables 'obj_type', 'segments', and
    'wireframe'.  These are _live_ variables, which are transparently 
    updated by GLUI ***/
  
  if ( obj_type == 0 ) {
    if ( wireframe )      
      glutWireSphere( .6, segments, segments );
    else                  
      glutSolidSphere( .6, segments, segments );
  }
  else if ( obj_type == 1 ) {
    if ( wireframe )
      glutWireTorus( .2,.5,16,segments );
    else
      glutSolidTorus( .2,.5,16,segments );
  }
  else if ( obj_type == 2 ) {
    if ( wireframe )
      glutWireTeapot( .5 );
    else
      glutSolidTeapot( .5 );
  }

  /* Disable lighting and set up ortho projection to render text */
  glDisable( GL_LIGHTING );  
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluOrtho2D( 0.0, 100.0, 0.0, 100.0  );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  glColor3ub( 0, 0, 0 );
  glRasterPos2i( 10, 10 );

  /*** Render the live character array 'text' ***/
  for (unsigned int i=0; i<text.length(); ++i)
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, text[i] );

  glEnable( GL_LIGHTING );

  glutSwapBuffers(); 
}


/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  /****************************************/
  /*   Initialize GLUT and create window  */
  /****************************************/

  glutInit(&argc, argv);
  glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
  glutInitWindowPosition( 50, 50 );
  glutInitWindowSize( 300, 300 );
 
  main_window = glutCreateWindow( "GLUI Example 3" );
  glutDisplayFunc( myGlutDisplay );
  glutReshapeFunc( myGlutReshape );  
  glutKeyboardFunc( myGlutKeyboard );
  glutMotionFunc( myGlutMotion );
  glutMouseFunc( myGlutMouse );

  /****************************************/
  /*       Set up OpenGL lights           */
  /****************************************/

  glEnable(GL_LIGHTING);
  glEnable( GL_NORMALIZE );

  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
  glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

  glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
  glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

  /****************************************/
  /*          Enable z-buferring          */
  /****************************************/

  glEnable(GL_DEPTH_TEST);

  /****************************************/
  /*         Here's the GLUI code         */
  /****************************************/

  printf( "GLUI version: %3.2f\n", GLUI_Master.get_version() );

  glui = GLUI_Master.create_glui( "GLUI", 0, 400, 50 ); /* name, flags,
							   x, and y */
  new GLUI_StaticText( glui, "GLUI Example 3" ); 
  obj_panel = new GLUI_Panel(glui, "Object" );

  /***** Control for the object type *****/

  GLUI_Panel *type_panel = new GLUI_Panel( obj_panel, "Type" );
  radio = new GLUI_RadioGroup(type_panel,&obj_type,4,control_cb);
  new GLUI_RadioButton( radio, "Sphere" );
  new GLUI_RadioButton( radio, "Torus" );
  new GLUI_RadioButton( radio, "Teapot" );

  checkbox = 
    new GLUI_Checkbox(obj_panel, "Wireframe", &wireframe, 1, control_cb );
  spinner =
    new GLUI_Spinner( obj_panel, "Segments:", &segments);
  spinner->set_int_limits( 3, 60 );
  spinner->set_alignment( GLUI_ALIGN_RIGHT );

  scale_spinner = 
    new GLUI_Spinner( obj_panel, "Scale:", &scale);
  scale_spinner->set_float_limits( .2f, 4.0 );
  scale_spinner->set_alignment( GLUI_ALIGN_RIGHT );

  new GLUI_Separator( obj_panel );
  edittext = new GLUI_EditText( obj_panel, "Text:", text );
  edittext->set_w( 150 );

  /******** Add some controls for lights ********/

  GLUI_Panel *light0 = new GLUI_Panel( glui, "Light 1" );
  GLUI_Panel *light1 = new GLUI_Panel( glui, "Light 2" );

  new GLUI_Checkbox( light0, "Enabled", &light0_enabled, 
                     LIGHT0_ENABLED_ID, control_cb );
  light0_spinner = 
    new GLUI_Spinner( light0, "Intensity:",
                      &light0_intensity, LIGHT0_INTENSITY_ID,
                      control_cb );
  light0_spinner->set_float_limits( 0.0, 1.0 );

  new GLUI_Checkbox( light1, "Enabled", &light1_enabled,
                     LIGHT1_ENABLED_ID, control_cb );
  light1_spinner = 
    new GLUI_Spinner( light1, "Intensity:", 
                      &light1_intensity, LIGHT1_INTENSITY_ID,
                      control_cb );
  light1_spinner->set_float_limits( 0.0, 1.0 );
  light1_spinner->disable();   /* Disable this light initially */

  /****** Add a grayed-out counter *****/
  
  GLUI_EditText *counter_edittext = 
    new GLUI_EditText( glui, "Count:", &counter );
  counter_edittext->disable();

  /****** Button to Open Command Line Window ******/
  open_console_btn = 
    new GLUI_Button(glui, "Open Console", OPEN_CONSOLE_ID, pointer_cb);

  /****** A 'quit' button *****/

  new GLUI_Button(glui, "Quit", 0,(GLUI_Update_CB)exit );

  /**** Link windows to GLUI, and register idle callback ******/
  
  glui->set_main_gfx_window( main_window );

  /* We register the idle callback with GLUI, not with GLUT */
  GLUI_Master.set_glutIdleFunc( myGlutIdle );

  /**** Regular GLUT main loop ****/  
  glutMainLoop();

  return EXIT_SUCCESS;
}


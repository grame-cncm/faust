/****************************************************************************

  A simple GLUT program using the GLUI User Interface Library

  This program sets up a checkbox and a spinner, both with live variables.
  No callbacks are used.

  -----------------------------------------------------------------------
  9/17/04 John Kew - Natural Selection, Inc. (jkew@natural-selection.com)   
  9/9/98 Paul Rademacher (rademach@cs.unc.edu)

****************************************************************************/

#include <string.h>
#include <GL/glui.h>

/** These are the live variables passed into GLUI ***/
int main_window;
int num_display  = 0;
int num_format  = 0;
int enable_textbox = 0;
GLUI_StaticText  *text;
GLUI_List        *hah;
GLUI_TextBox     *moo;
GLUI             *tree;
GLUI_TreePanel   *tp;
GLUI_FileBrowser *fb;
GLUI_EditText    *bedit;

const char general[] =
  "GLUI 2.3 Widgets\n"
  "\n"
  "A number of widgets have been introduced in GLUI 2.3\n"
  "\n"
  "  * GLUI_Scrollbar   - A scrollbar slider widget\n"
  "  * GLUI_TextBox     - A multi-line text widget\n"
  "  * GLUI_List        - A static choice list\n"
  "  * GLUI_FileBrowser - A simple filebrowser based on GLUI_List\n"
  "  * GLUI_Tree        - Hierarchical tree widget\n"
  "  * GLUI_TreePanel   - Manager for the tree widget\n";

const char scroll[] = 
  "Scrollbar Widget\n"
  "\n"
  "The GLUI_Scrollbar can be used more or less like a GLUI_Spinner.\n"
  "It can be horizontal or vertical, and have float or int values.\n"
  "\n"
  "The set_int_limits and set_float_limits functions work properly even\n"
  "if the min and max values are reversed.  In this way you can choose\n"
  "whether the left/right or top/bottom is the minimum value.  \n"
  "\n"
  "For instance, with set_int_limits(0, 100) you get a normal slider with\n"
  "0 corresponding to the left (bottom) end, and 100 corresponding to the\n"
  "right (top) end.\n"
  "\n"
  "By calling set_int_limits(100,0) instead, the right (top) end becomes 0,\n"
  "and the left (bottom) end is 100.\n";

const char tree_txt[] = "Tree Widget";

const char commandline[] = 
  "CommandLine Widget\n"
  "\n"
  "The GLUI_CommandLine is a GLUI_EditText with some special functionality\n"
  "useful for implementing a simple command-line style input widget.\n"
  "The main feature is that it maintains a command history buffer so that\n"
  "users can recall previous commands.\n";

const char gstring[] = 
  "GLUI_String\n"
  "\n"
  "The GLUI string class used to be wrapper class around \n"
  "a fixed 300 char buffer.\n"
  "Now GLUI_String is just a typedef for std::string.\n"
  "\n"
  "One new function has been introduced, which is a sprintf() equivalent\n"
  "for std::string/GLUI_String.\n"
  "\n"
  "  glui_format_str(GLUI_String& str, const char *format_str, ...);\n"
  "\n"
  "Other than the fact that it takes a GLUI_String as the first argument,\n"
  "it works just like sprintf().\n";

const char list[] =
  "List Widget\n"
  "\n"
  "As seen on the left side of this window.";

const char filebrowser[] = 
  "FileBrowserWidget\n"
  "\n"
  "As seen in the lower left corner of this window.\n"
  "\n"
  "The GLUI_FileBrowser is a subclass of GLUI_List and provides,\n"
  "a simple file browsing and selecting interface under Windows and Unix.\n"
  "\n"
  "Go ahead and give it a try!  Navigate and select files by double-clicking.\n"
  "If you pick a text file it will be displayed in this GLUI_TextBox.\n";

const char text_box[] = 
  "TextBox w/ optional Scrollbar\n"
  "\n"
  "A TextBox is a multiline editing box that supports basic navigation, \n"
  "formatting, and editing capabilities. These are text block selection, \n"
  "tabs, new lines, arrow key navigation, as well as an optional scrollbar. \n"
  "The scrollbar is actually a distinct widget and can exist by itself, or \n"
  "be associated with objects that have a specified callback routine.\n"
  "\n"
  "new GLUI_TextBox\n"
  "Adds a new textbox to a GLUI window, optionally nested within another \n"
  "rollout or panel.\n"
  "\n"
  "Usage:\n"
  "new GLUI_TextBox(GLUI_Node *glui_or_panel, char *live_var=NULL,\n"
  "  int scroll = false,\n"
  "  int id=-1,\n"
  "  GLUI_Update_CB callback=NULL );\n"
  "\n"
  "  panel    - Name of panel to place the TextBox in.\n"
  "  live_var - Currently unimplemented, this might be used\n"
  "             in future iterations.\n"
  "  scroll   - set to \"true\" if you want a scrollbar on the left side\n"
  "  id       - If callback is defined, it will be passed this integer\n"
  "             when the value is modified.\n"
  "  callback - Pointer to callback function of type (*)(int)\n"
  "\n"
  "Notes:\n"
  "The scrollbar widget uses a different callback scheme to communicate with \n"
  "the textbox. Any object wishing to utilize a scrollbar in some way should \n"
  "implement a static function in the object with the signature:\n"
  "\n"
  "(*)(GLUI_Control *, int)\n"
  "\n"
  "Where the first parameter is the object the scrollbar is associated with \n"
  "and the second is the int_val passed into the object by the scrollbar.\n"
  "Refer to glui_textbox.cpp and glui_scrollbar.cpp for implementation details.\n"
  "\n"
  "Wishlist:\n"
  "* Word Wrap\n"
  "* Optimized Drawing (Update only lines that change, etc.)\n"
  "* Multicolour text\n"
  "* Current word selection\n"
  "* copy/paste\n";
  
/*Bugs:\n\
 * fewer Mouse Drag calls  with large texts\n\
 * Insertion Pt sometimes drawn on wrong line.\n\
 * The scrollbar tab does not exactly match mouse position.\n\
 * Two tabs cannot be placed next to each other in a string without a space between them.\n\
 * Occasional horizontal drawing overruns.\n\
 * set_text seems to like being called after all the windows are open for large amounts of text. If you try it with a string longer than 195 characters it seems to trucate it to 195.\n\
 \n\
 ";
*/

/***************************************** myGlutDisplay() *****************/

void control_cb(int control) {
  int item;
  GLUI_String text;
  std::string file_name;
  FILE  *file;
  char c;
  int i;
  int format;
  glutPostRedisplay();
  item = hah->get_current_item();
  
  if (control == 7) {
    i = 0;
    file_name = "";
    file_name = fb->get_file();
    file = fopen(file_name.c_str(),"r"); 
    if (file == NULL) 
      printf("Error opening file\n");
    else {
      do {
        c = getc(file);
        text += c;
        i++;
      } while (c != EOF);
      fclose(file);
    } 

    moo->set_text(text.c_str());
  }


  if ( control == 1 ) {
    tree->hide();
    if (item==0) {
      moo->set_text(general);
    }
    if (item==1) {
      moo->set_text(text_box);
    }
    if (item==2) {
      moo->set_text(scroll);
    }
    if (item==3) {
      moo->set_text(gstring);
    }
    if (item==4) {
      moo->set_text(commandline);
    }
    if (item==5) {
      tree->show();
      moo->set_text(tree_txt);
    }
    if (item==6) {
      moo->set_text(list);
    }
    if (item==7) {
      moo->set_text(filebrowser);
    }
  }
  if ( control == 2) {
    tp->ab("foo");
  }
  if ( control == 3) {
      tp->db();
  }
  if ( control == 4) {
    tp->fb();
  }
  if ( control == 5) {
      tp->resetToRoot();
  }
  if ( control == 6) {
      tp->descendBranch();
  }
  if ( control == 8) {
      tp->next();
  }
  if ( control == 9) {
      tp->expand_all();
  }
  if ( control == 10) {
      tp->collapse_all();
  }
  if ( control == 11) {
    format = 0; 
    format = GLUI_TREEPANEL_ALTERNATE_COLOR | 
      GLUI_TREEPANEL_CONNECT_CHILDREN_ONLY;
    
    if (num_display)
      format = format | GLUI_TREEPANEL_DISPLAY_HIERARCHY;
    if (num_format)
      format = format | GLUI_TREEPANEL_HIERARCHY_NUMERICDOT;
    else
      format = format | GLUI_TREEPANEL_HIERARCHY_LEVEL_ONLY;
    tp->set_format(format);
    tp->update_all();
  }
  if (control == 12) {
    if (enable_textbox) {
      moo->enable();
    } else {
      moo->disable();
    }
  }
}

//void out_of_memory() {
//  printf("Out of memory!\n\n");
//} 

/**************************************** main() ********************/

int main(int argc, char* argv[])
{
  glutInit(&argc, argv);

  GLUI *edit = GLUI_Master.create_glui("Help on GLUI Widgets", 0);
  main_window = edit->get_glut_window_id();
  GLUI_Panel *ep = new GLUI_Panel(edit,"",true);
  new GLUI_StaticText(ep,"Widget Information:");
  hah = new GLUI_List(ep,true,1,control_cb);
  hah->add_item(0,"GLUI 2.3");
  hah->add_item(1,"TextBox");
  hah->add_item(2,"Scrollbar");
  hah->add_item(3,"GLUI_String");
  hah->add_item(4,"CommandLine");
  hah->add_item(5,"Tree");
  hah->add_item(6,"List");
  hah->add_item(7,"FileBrowser");
  new GLUI_StaticText(ep,"Open Text File:");
  fb = new GLUI_FileBrowser(ep, "", false, 7, control_cb);
  fb->set_h(180);
  hah->set_h(180);
  new GLUI_Column(ep,false); 

  moo = new GLUI_TextBox(ep,true);
  moo->set_text(general);
  moo->set_h(400);
  moo->set_w(410);
  moo->disable();
  enable_textbox=0;
  new GLUI_Checkbox(ep, "Enable text box:",&enable_textbox,12,control_cb);

  tree = GLUI_Master.create_glui("Tree Test", 0);
  ep = new GLUI_Panel(tree, "Tree Controls");
  bedit = new GLUI_EditText(ep, "New Branch Name:");
  new GLUI_Checkbox(ep, "Display Numbers", &num_display);
  new GLUI_StaticText(ep, "Number format:");
  GLUI_RadioGroup *rg = new GLUI_RadioGroup(ep, &num_format);
  new GLUI_RadioButton(rg, "Level Only");
  new GLUI_RadioButton(rg, "Hierarchal");
  new GLUI_Button(ep, "Update Format", 11, control_cb); 
  new GLUI_Column(ep);
  new GLUI_Button(ep, "Add Branch", 2, control_cb); 
  new GLUI_Button(ep, "Del Branch", 3, control_cb);
  new GLUI_Button(ep, "Up Branch", 4, control_cb); 
  new GLUI_Button(ep, "Goto Root", 5, control_cb);
  new GLUI_Column(ep);
  new GLUI_Button(ep, "Descend to Leaf", 6, control_cb); 
  new GLUI_Button(ep, "Next Branch", 8, control_cb); 
  new GLUI_Button(ep, "Expand All", 9, control_cb); 
  new GLUI_Button(ep, "Collapse All", 10, control_cb); 
  tp = new GLUI_TreePanel(tree,"Tree Test");
  tp->set_format(GLUI_TREEPANEL_ALTERNATE_COLOR | 
                 GLUI_TREEPANEL_CONNECT_CHILDREN_ONLY |
                 GLUI_TREEPANEL_DISPLAY_HIERARCHY | 
                 GLUI_TREEPANEL_HIERARCHY_NUMERICDOT);
  tp->set_level_color(1,1,1);
  tp->ab("foo you");
  tree->hide();
 
  edit->set_main_gfx_window(main_window); 
  tree->set_main_gfx_window(main_window); 

  glutMainLoop();
  return 0;
}




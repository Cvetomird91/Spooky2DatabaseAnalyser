#include <iostream>
#include <iterator>
#include <string>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.h>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Text_Display.H>

#include <boost/filesystem.hpp>

#include "Spooky2DatabaseAnalyser.h"

using namespace boost::filesystem;

Fl_Input *search_string;
Fl_Output *output_search;
Spooky2DatabaseAnalyser *parser;
std::stringstream *stream;

void button_cb(Fl_Widget *obj, void* data) {
    obj->redraw();

    const char *start_dir = std::getenv("HOME");
    Fl_Native_File_Chooser *native = new Fl_Native_File_Chooser(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
    native->directory( start_dir );
    native->title( "Select a directory");

    native->type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
    std::string *directoryName = new std::string();

    switch (native->show()) {
      case -1: break; //fprintf(stderr, "ERROR: %s\n", native.errmsg()); break; // ERROR
      case  1: break; //fprintf(stderr, "*** CANCEL\n"); fl_beep(); break;    // CANCEL
      default:                            // PICKED FILE
          if (native->filename())
            *directoryName = native->filename();
          break;
    }

    std::string search(search_string->value());

    std::cout << search << std::endl;
    std::cout << *directoryName << std::endl;

    //additional window
    Fl_Window* adw = new Fl_Window (10,10,600,400);
    adw->begin();
    adw->show();

    Fl_Text_Buffer *buff = new Fl_Text_Buffer();
    Fl_Text_Display *disp = new Fl_Text_Display(40, 40, 350, 150, "Display");
    disp->buffer(buff);

    if (search.length() != 0) {
        parser = new Spooky2DatabaseAnalyser(*directoryName, search);
        parser->gatherResults();

        stream = parser->getResultsStream();

        buff->text(search.c_str());

        delete stream;
    }

    adw->end();
    adw->add(disp);
}

int main(int argc, char* argv[]) {

    Fl_Double_Window *window;

    window = new Fl_Double_Window (640, 480);
    window->begin();

    Fl_Button* button = new Fl_Button(0, 0, 120, 40, "Open directory");
    search_string  = new Fl_Input( 320,  10, 140, 30, "Search string");
    button->callback((Fl_Callback*)button_cb);

    window->show();

    window->end();

    delete parser;
    delete stream;
    return(Fl::run());
}

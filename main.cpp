/******************************************************************************************\
*                                                                                          *
*   main.cpp                                                                               *
*                                                                                          *
*       Main function for OpenAuraSDK GUI project                                          *
*                                                                                          *
\******************************************************************************************/

#include "NetworkServer.h"
#include "OpenRGB.h"
#include "ProfileManager.h"
#include "RGBController.h"
#include "i2c_smbus.h"
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "OpenRGBDialog2.h"


extern std::vector<i2c_smbus_interface*> busses;
extern std::vector<RGBController*> rgb_controllers;

/*-------------------------------------------------------------*\
| Command line functionality and return flags                   |
\*-------------------------------------------------------------*/
extern unsigned int cli_main(int argc, char *argv[], std::vector<RGBController *> rgb_controllers_in, ProfileManager* profile_manager_in, NetworkServer* network_server_in);

enum
{
    RET_FLAG_PRINT_HELP     = 1,
    RET_FLAG_START_GUI      = 2,
    RET_FLAG_I2C_TOOLS      = 4,
};

/******************************************************************************************\
*                                                                                          *
*   main                                                                                   *
*                                                                                          *
*       Main function.  Detects busses and Aura controllers, then opens the main window    *
*                                                                                          *
\******************************************************************************************/

int main(int argc, char* argv[])
{
    ProfileManager profile_manager(rgb_controllers);
    NetworkServer server(rgb_controllers);
    
    DetectRGBControllers();

    profile_manager.LoadSizeFromProfile("sizes.ors");

    /*---------------------------------------------------------*\
    | Process command line arguments                            |
    \*---------------------------------------------------------*/
    unsigned int ret_flags = RET_FLAG_START_GUI;
    if(argc > 1)
    {
        ret_flags = cli_main(argc, argv, rgb_controllers, &profile_manager, &server);
    }

    /*---------------------------------------------------------*\
    | If the command line parser indicates that the GUI should  |
    | run, or if there were no command line arguments, start the|
    | GUI.                                                      |
    \*---------------------------------------------------------*/
    if(ret_flags & RET_FLAG_START_GUI)
    {
        QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
        QApplication a(argc, argv);

        bool show_i2c_tools = false;
        if(ret_flags & RET_FLAG_I2C_TOOLS)
        {
            //I2C Tools is enabled
            show_i2c_tools = true;
        }

        Ui::OpenRGBDialog2 dlg(busses, rgb_controllers, &profile_manager, &server, show_i2c_tools);
        dlg.show();

        return a.exec();
    }
    else
    {
        return 0;
    }
}

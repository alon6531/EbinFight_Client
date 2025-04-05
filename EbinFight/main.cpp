#include "Client.h"
#include "Engine.h"

int main()
{
    float i = 0;
    Client client = Client();
    

    Engine* app =new Engine(client);
    app->Run();
    
    delete app;
    return 0;
}
#include "Client.h"
#include "Engine.h"

int main()
{
    float i = 0;
    Client client = Client("alon");
    
    if (client.connect())
    {
        Engine* app = new Engine(client);
        app->Run();
        delete app;
    }

    

    return 0;
}
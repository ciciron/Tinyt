#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <unistd.h>
#include <getopt.h>
#include "tsapi.h"
#include "abuser.h"

int verbose_flag = 0;
int test_flag = 0;

int main(int argc, char *argv[])
{
    int objects = 35;
    int comms = 100;
    while (1)
    {
        static struct option long_options[] =
        {
          {"verbose",  no_argument,       &verbose_flag, 1},
          {"test",     no_argument,       &test_flag, 1},
          {"help",     no_argument,       0, 'h'},
          {"objects",  required_argument, 0, 'o'},
          {"commands", required_argument, 0, 'c'},
          {0, 0, 0, 0}
        };
        int option_index = 0;
        int c = getopt_long (argc, argv, "abc:d:f:",
                       long_options, &option_index);
        if (c == -1)
            break;

        switch (c)
        {
            case 0:
                if (long_options[option_index].flag != 0)
                    break;
                printf ("option %s", long_options[option_index].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;
            case '?':
            case 'h':
                puts("Use:\n");
                puts("TinyTestServer --help or -h");
                puts("TinyTestServer --verbose");
                puts("TinyTestServer --test");
                puts("TinyTestServer --objects N (default - 35 pcs)");
                puts("TinyTestServer --commands M (default - 100 pcs)");
                return 0;

            case 'o':
                try
                {
                    objects = std::stoi(optarg);
                } catch (...)
                {
                    puts("Invalid --objects argument. Terminate.");
                    return -1;
                }
                break;
            case 'c':
                try
                {
                    comms = std::stoi(optarg);
                } catch (...)
                {
                    puts("Invalid --objects argument. Terminate.");
                    return -1;
                }
                break;
            default:
                puts("Unknown option. For more info please use:\nTinyTestServer --help\n"); 
                return 0;
        }
    }
    IServer *ies = EntryPoint();
    if (!ies)
    {
        puts("Tinyt: Service entry point failed.");
        return -1;
    }
    if (test_flag)
    {
        //Run realm test(s)
        switch (ies->Test())
        {
            case RStatus::Success:
                puts("Tinyt: Test success.");
                break;
            case RStatus::Refuse:
                puts("Tinyt: Test failed.");
                break;
            default:
                puts("Tinyt: Test return unknown status. WTF?!");
                break;
        }
    }
    //verbose_flag = 1;
    //test_flag = 1;
    auto client = Abuser::Create(ies, objects);
    if (client)
    {
        client->DoAbuse(comms);
    }
    
    return 0;
}
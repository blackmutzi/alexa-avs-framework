#include "include/utils/console.hpp"

using namespace AVS;

Console::Console()
    : m_thread_status( false )
{}
Console::~Console(){}

void Console::initialize(void)
{
    setThreadStatus( true );
    boost::thread console_thread( &Console::onConsoleThread , this );
}

void Console::setThreadStatus(bool status)
{
    m_thread_status = status;
}

bool Console::getThreadStatus(void)
{
    return m_thread_status;
}

void Console::onConsoleThread(Console *console)
{
    // Feld zur Aufnahme der Eingabe definieren
    size_t size = 82;
    char array[size];

    while( console->getThreadStatus() )
    {
        std::cin.getline( array , size );
        array[size-1] = 0;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        console->onConsoleInputEvent( array );
    }
}



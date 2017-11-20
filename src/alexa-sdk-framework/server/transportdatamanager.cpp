#include "include/server/transportdatamanager.hpp"

using namespace Server;

TransportDataManager::TransportDataManager(){}
TransportDataManager::~TransportDataManager(){}

TransportInfo * TransportDataManager::createTransportData(char *data, size_t size)
{
    TransportInfo * info = new TransportInfo();
    info->copy( data , size );
    return info;
}

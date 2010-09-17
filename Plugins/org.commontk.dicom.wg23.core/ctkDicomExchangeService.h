/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/


#ifndef CTKDICOMEXCHANGESERVICE_H
#define CTKDICOMEXCHANGESERVICE_H

#include <ctkDicomExchangeInterface.h>
#include <QScopedPointer>
#include <org_commontk_dicom_wg23_core_Export.h>

class ctkDicomServicePrivate;

class org_commontk_dicom_wg23_core_EXPORT ctkDicomExchangeService : public ctkDicomExchangeInterface
{

public:
  ctkDicomExchangeService(ushort port, QString path);
  ~ctkDicomExchangeService();

  bool notifyDataAvailable(ctkDicomWG23::AvailableData data, bool lastData);
  QList<ctkDicomWG23::ObjectLocator> *getData(QList<QUuid> objectUUIDs,
                                             QList<QString> acceptableTransferSyntaxUIDs, bool includeBulkData);
  void releaseData(QList<QUuid> objectUUIDs);


protected:
  ctkDicomServicePrivate * d;
};
#endif // CTKDICOMEXCHANGESERVICE_H

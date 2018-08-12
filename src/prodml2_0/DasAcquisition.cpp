/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#include "prodml2_0/DasAcquisition.h"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "H5Tpublic.h"

#include "prodml2_0/FiberOpticalPath.h"
#include "prodml2_0/DasInstrumentBox.h"
#include "prodml2_0/HdfProxy.h"

#include "tools/TimeTools.h"
#include "tools/GuidTools.h"

using namespace std;
using namespace PRODML2_0_NS;
using namespace gsoap_eml2_1;
using namespace epc;

const char* DasAcquisition::XML_TAG = "DasAcquisition";

DasAcquisition::DasAcquisition(FiberOpticalPath* fiberOpticalPath, class DasInstrumentBox* dasInstrumentBox,
	const string & guid, const string & title,
	const std::string & jobUuid, const std::string & facilityId, const std::string & vendorName,
	const double & pulseRate, const gsoap_eml2_1::eml21__FrequencyUom & pulseRateUom,
	const double & pulseWidth, const gsoap_eml2_1::eml21__TimeUom & pulseWidthUom,
	const double & gaugeLength, const gsoap_eml2_1::eml21__LengthUom & gaugeLengthUom,
	const double & spatialSamplingInterval, const gsoap_eml2_1::eml21__LengthUom & spatialSamplingIntervalUom,
	const double & minimumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & minimumFrequencyUom,
	const double & maximumFrequency, const gsoap_eml2_1::eml21__FrequencyUom & maximumFrequencyUom,
	const ULONG64 & lociCount, const ULONG64 & startLocusIndex,
	const std::string & measurementStartIsoTime, bool triggeredMeasurement)
{
	if (fiberOpticalPath == nullptr)
		throw invalid_argument("The fiber Optical Path cannot be null.");

	gsoapProxy2_1 = soap_new_prodml2__DasAcquisition(fiberOpticalPath->getGsoapContext(), 1);
	soap* soapContext = getGsoapContext();

	initMandatoryMetadata();
	setMetadata(guid, title, "", -1, "", "", -1, "", "");

	setFiberOpticalPath(fiberOpticalPath);
	setDasInstrumentBox(dasInstrumentBox);

	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	da->AcquisitionId = jobUuid;
	da->FacilityId.push_back(facilityId);
	da->VendorCode = soap_new_prodml2__BusinessAssociate(soapContext, 1);
	da->VendorCode->Name = vendorName;

	da->PulseRate = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->PulseRate->__item = pulseRate;
	da->PulseRate->uom = pulseRateUom;

	da->PulseWidth = soap_new_eml21__TimeMeasure(soapContext, 1);
	da->PulseWidth->__item = pulseWidth;
	da->PulseWidth->uom = pulseWidthUom;

	da->GaugeLength = soap_new_eml21__LengthMeasure(soapContext, 1);
	da->GaugeLength->__item = gaugeLength;
	da->GaugeLength->uom = gaugeLengthUom;

	da->SpatialSamplingInterval = soap_new_eml21__LengthMeasure(soapContext, 1);
	da->SpatialSamplingInterval->__item = spatialSamplingInterval;
	da->SpatialSamplingInterval->uom = spatialSamplingIntervalUom;

	da->MinimumFrequency = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->MinimumFrequency->__item = minimumFrequency;
	da->MinimumFrequency->uom = minimumFrequencyUom;

	da->MaximumFrequency = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->MaximumFrequency->__item = maximumFrequency;
	da->MaximumFrequency->uom = maximumFrequencyUom;

	da->NumberOfLoci = lociCount;
	da->StartLocusIndex = startLocusIndex;

	da->MeasurementStartTime = measurementStartIsoTime;
	da->TriggeredMeasurement = triggeredMeasurement;
}

DasAcquisition::DasAcquisition(FiberOpticalPath* fiberOpticalPath, DasInstrumentBox* dasInstrumentBox,
	PRODML2_0_NS::HdfProxy * proxy)
{
	setHdfProxy(proxy);

	gsoapProxy2_1 = soap_new_prodml2__DasAcquisition(proxy->getGsoapContext(), 1);
	soap* soapContext = getGsoapContext();
	
	initMandatoryMetadata();
	string uuid = proxy->readStringAttribute("Acquisition", "uuid");
	setMetadata(uuid, "Fake/Virtual Das Acquisition", "", -1, "", "", -1, "", "");
	
	setFiberOpticalPath(fiberOpticalPath);
	setDasInstrumentBox(dasInstrumentBox);
	
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	da->AcquisitionId = proxy->readStringAttribute("Acquisition", "AcquisitionId");
	da->FacilityId = proxy->readStringArrayAttribute("Acquisition", "FacilityId");
	da->VendorCode = soap_new_prodml2__BusinessAssociate(soapContext, 1);
	da->VendorCode->Name = proxy->readStringAttribute("Acquisition", "VendorCode");
	
	da->PulseRate = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->PulseRate->__item = proxy->readDoubleAttribute("Acquisition", "PulseRate");
	da->PulseRate->uom = gsoap_eml2_1::eml21__FrequencyUom__EHz; // This uom is not part of the HDF5 dataset attribute collection so far.
	
	da->PulseWidth = soap_new_eml21__TimeMeasure(soapContext, 1);
	da->PulseWidth->__item = proxy->readDoubleAttribute("Acquisition", "PulseWidth");
	gsoap_eml2_1::soap_s2eml21__TimeUom(soapContext, proxy->readStringAttribute("/Acquisition", "PulseWidthUnit").c_str(), &da->PulseWidth->uom);
	
	da->GaugeLength = soap_new_eml21__LengthMeasure(soapContext, 1);
	da->GaugeLength->__item = proxy->readDoubleAttribute("Acquisition", "GaugeLength");
	gsoap_eml2_1::soap_s2eml21__LengthUom(soapContext, proxy->readStringAttribute("/Acquisition", "GaugeLengthUnit").c_str(), &da->GaugeLength->uom);
	
	da->SpatialSamplingInterval = soap_new_eml21__LengthMeasure(soapContext, 1);
	da->SpatialSamplingInterval->__item = proxy->readDoubleAttribute("Acquisition", "SpatialSamplingInterval");
	gsoap_eml2_1::soap_s2eml21__LengthUom(soapContext, proxy->readStringAttribute("/Acquisition", "SpatialSamplingIntervalUnit").c_str(), &da->SpatialSamplingInterval->uom);
	
	da->MinimumFrequency = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->MinimumFrequency->__item = proxy->readDoubleAttribute("Acquisition", "MinimumFrequency");
	da->MinimumFrequency->uom = gsoap_eml2_1::eml21__FrequencyUom__EHz; // This uom is not part of the HDF5 dataset attribute collection so far.

	da->MaximumFrequency = soap_new_eml21__FrequencyMeasure(soapContext, 1);
	da->MaximumFrequency->__item = proxy->readDoubleAttribute("Acquisition", "MaximumFrequency");
	da->MaximumFrequency->uom = gsoap_eml2_1::eml21__FrequencyUom__EHz; // This uom is not part of the HDF5 dataset attribute collection so far.

	da->NumberOfLoci = proxy->readLongAttribute("Acquisition", "NumberOfLoci");
	da->StartLocusIndex = proxy->readLongAttribute("Acquisition", "StartLocusIndex");

	da->MeasurementStartTime = proxy->readStringAttribute("Acquisition", "MeasurementStartTime");
	da->TriggeredMeasurement = proxy->readLongAttribute("Acquisition", "TriggeredMeasurement") != 0;

	// Raw
	ostringstream oss;
	oss << "Acquisition/Raw[" << da->Raw.size() << "]";
	string hdfGroup = oss.str();
	while (proxy->exist(hdfGroup)) {
		vector<std::string> hdfDimensionsStr = proxy->readStringArrayAttribute(hdfGroup + "/RawData", "Dimensions");
		gsoap_eml2_1::prodml2__DasDimensions slowestHdfDimension;
		gsoap_eml2_1::prodml2__DasDimensions fastestHdfDimension;
		soap_s2prodml2__DasDimensions(soapContext, hdfDimensionsStr[0].c_str(), &slowestHdfDimension);
		soap_s2prodml2__DasDimensions(soapContext, hdfDimensionsStr[1].c_str(), &fastestHdfDimension);

		pushBackRawXmlOnly(proxy->readStringAttribute(hdfGroup, "uuid"),
			proxy->readStringAttribute(hdfGroup, "RawDataUnit"),
			proxy->readLongAttribute(hdfGroup, "StartLocusIndex"),
			proxy->readLongAttribute(hdfGroup, "NumberOfLoci"),
			proxy->readStringAttribute(hdfGroup, "RawDescription"),
			proxy->readStringAttribute(hdfGroup + "/RawDataTime", "StartTime"),
			proxy->readStringAttribute(hdfGroup + "/RawDataTime", "EndTime"),
			proxy->readLongAttribute(hdfGroup + "/RawDataTime", "Count"),
			slowestHdfDimension, fastestHdfDimension,
			proxy->getHdfDatatypeClassInDataset(hdfGroup + "/RawData") == H5T_INTEGER,
			proxy);

		oss.clear();
		oss << "Acquisition/Raw[" << da->Raw.size() << "]";
		hdfGroup = oss.str();
	}

}

COMMON_NS::AbstractHdfProxy* DasAcquisition::getHdfProxy() const
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = static_cast<COMMON_NS::AbstractHdfProxy*>(epcDocument->getResqmlAbstractObjectByUuid(getHdfProxyUuid()));
	if (hdfProxy != nullptr && !hdfProxy->isOpened()) {
		hdfProxy->open();
	}
	return hdfProxy;
}

std::string DasAcquisition::getHdfProxyUuid() const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	if (da->Raw.empty()) {
		throw logic_error("The Das acquisition instance must have at least one Raw defined.");
	}
	eml21__IntegerExternalArray* hdfValues = da->Raw[0]->RawDataTime->__DasTimeArray_sequence->TimeArray;

	return hdfValues->Values->ExternalFileProxy[0]->EpcExternalPartReference->Uuid;
}

void DasAcquisition::setHdfProxy(COMMON_NS::AbstractHdfProxy * proxy)
{
	if (proxy == nullptr) {
		throw invalid_argument("The hdf proxy of das acquisiiton " + getUuid() + " cannot be null");
	}

	if (std::find(proxy->dasAcquisitionSourceObject.begin(), proxy->dasAcquisitionSourceObject.end(), this) == proxy->dasAcquisitionSourceObject.end()) {
		proxy->dasAcquisitionSourceObject.push_back(this);
	}
}

gsoap_eml2_1::eml21__DataObjectReference* DasAcquisition::getFiberOpticalPathDor() const
{
	return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->OpticalPath;
}

FiberOpticalPath* DasAcquisition::getFiberOpticalPath() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<FiberOpticalPath>(getFiberOpticalPathDor()->Uuid);
}

void DasAcquisition::setFiberOpticalPath(FiberOpticalPath* fiberOpticalPath)
{
	if (fiberOpticalPath == nullptr) {
		throw invalid_argument("Cannot set a null fiberOpticalPath to a das acquisition");
	}

	// EPC
	fiberOpticalPath->dasAcquisitionSet.push_back(this);

	// XML
	if (updateXml) {
		_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
		da->OpticalPath = fiberOpticalPath->newEmlReference();
	}
}

gsoap_eml2_1::eml21__DataObjectReference* DasAcquisition::getDasInstrumentBoxDor() const
{
	return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->DasInstrumentBox;
}

DasInstrumentBox* DasAcquisition::getDasInstrumentBox() const
{
	return getEpcDocument()->getResqmlAbstractObjectByUuid<DasInstrumentBox>(getDasInstrumentBoxDor()->Uuid);
}

void DasAcquisition::setDasInstrumentBox(DasInstrumentBox* dasInstrumentBox)
{
	if (dasInstrumentBox == nullptr) {
		throw invalid_argument("Cannot set a null DasInstrumentBox to a das acquisition");
	}

	// EPC
	dasInstrumentBox->dasAcquisitionSet.push_back(this);

	// XML
	if (updateXml) {
		_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
		da->DasInstrumentBox = dasInstrumentBox->newEmlReference();
	}
}

vector<Relationship> DasAcquisition::getAllEpcRelationships() const
{
	vector<Relationship> result;
	
	FiberOpticalPath* fop = getFiberOpticalPath();
	Relationship relFop(fop->getPartNameInEpcDocument(), "", fop->getUuid());
	relFop.setDestinationObjectType();
	result.push_back(relFop);

	DasInstrumentBox* dib = getDasInstrumentBox();
	Relationship relDib(dib->getPartNameInEpcDocument(), "", dib->getUuid());
	relDib.setDestinationObjectType();
	result.push_back(relDib);

	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();
	Relationship relHdf(hdfProxy->getPartNameInEpcDocument(), "", hdfProxy->getUuid());
	relHdf.setMlToExternalPartProxyType();
	result.push_back(relHdf);

	return result;
}

void DasAcquisition::initHdfAttributes()
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	soap* soapContext = getGsoapContext();
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();

	// STRING
	std::vector<std::string> attributeStringValues;
	for (size_t i = 0; i < da->FacilityId.size(); ++i) {
		attributeStringValues.push_back(da->FacilityId[i]);
	}
	hdfProxy->writeGroupAttribute("Acquisition", "FacilityId", attributeStringValues);

	std::vector<std::string> attributeNames;
	attributeNames.push_back("schemaVersion");
	attributeNames.push_back("uuid");
	attributeNames.push_back("Title");
	attributeNames.push_back("Creation");
	attributeNames.push_back("Format");
	attributeNames.push_back("AcquisitionId");
	attributeNames.push_back("VendorCode");
	attributeNames.push_back("PulseWidthUnit");
	attributeNames.push_back("GaugeLengthUnit");
	attributeNames.push_back("SpatialSamplingIntervalUnit");
	attributeNames.push_back("MeasurementStartTime");

	attributeStringValues.clear();
	attributeStringValues.push_back(da->schemaVersion);
	attributeStringValues.push_back(da->uuid);
	attributeStringValues.push_back(da->Citation->Title);
	char buf[20]; // 19 for the string below +1 for the terminating char
	strftime(buf, 20, "%Y-%m-%dT%H:%M:%S", &da->Citation->Creation);
	attributeStringValues.push_back(buf);
	attributeStringValues.push_back(da->Citation->Format);
	attributeStringValues.push_back(da->AcquisitionId);
	attributeStringValues.push_back(da->VendorCode->Name);
	attributeStringValues.push_back(gsoap_eml2_1::soap_eml21__TimeUom2s(soapContext, da->PulseWidth->uom));
	attributeStringValues.push_back(gsoap_eml2_1::soap_eml21__LengthUom2s(soapContext, da->GaugeLength->uom));
	attributeStringValues.push_back(gsoap_eml2_1::soap_eml21__LengthUom2s(soapContext, da->SpatialSamplingInterval->uom));
	attributeStringValues.push_back(da->MeasurementStartTime);

	hdfProxy->writeGroupAttributes("Acquisition", attributeNames, attributeStringValues);

	// DOUBLE
	attributeNames.clear();
	attributeNames.push_back("PulseRate");
	attributeNames.push_back("PulseWidth");
	attributeNames.push_back("GaugeLength");
	attributeNames.push_back("SpatialSamplingInterval");
	attributeNames.push_back("MinimumFrequency");
	attributeNames.push_back("MaximumFrequency");

	std::vector<double> attributeDoubleValues;
	attributeDoubleValues.push_back(da->PulseRate->__item);
	attributeDoubleValues.push_back(da->PulseWidth->__item);
	attributeDoubleValues.push_back(da->GaugeLength->__item);
	attributeDoubleValues.push_back(da->SpatialSamplingInterval->__item);
	attributeDoubleValues.push_back(da->MinimumFrequency->__item);
	attributeDoubleValues.push_back(da->MaximumFrequency->__item);

	hdfProxy->writeGroupAttributes("Acquisition", attributeNames, attributeDoubleValues);

	// INTEGER
	attributeNames.clear();
	attributeNames.push_back("NumberOfLoci");
	attributeNames.push_back("StartLocusIndex");
	attributeNames.push_back("TriggeredMeasurement");

	std::vector<int> attributeIntegerValues;
	attributeIntegerValues.push_back(da->NumberOfLoci);
	attributeIntegerValues.push_back(da->StartLocusIndex);
	attributeIntegerValues.push_back(da->TriggeredMeasurement ? 1 : 0);

	hdfProxy->writeGroupAttributes("Acquisition", attributeNames, attributeIntegerValues);
}

prodml2__DasRaw* DasAcquisition::pushBackRawXmlOnly(const std::string & uuid, const std::string & rawDataUnit, const ULONG64 & startLocusIndex, const ULONG64 & numberOfLoci, const std::string & rawDescription,
	const std::string & startTime, const std::string endTime, const ULONG64 & timeCount,
	gsoap_eml2_1::prodml2__DasDimensions slowestHdfDimension, gsoap_eml2_1::prodml2__DasDimensions fastestHdfDimension,
	bool datatypeIsInteger,
	COMMON_NS::AbstractHdfProxy* proxy)
{
	setHdfProxy(proxy);

	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);

	ostringstream oss;
	oss << "Acquisition/Raw[" << da->Raw.size() << "]";

	soap* soapContext = getGsoapContext();
	prodml2__DasRaw* dasRaw = soap_new_prodml2__DasRaw(soapContext, 1);
	da->Raw.push_back(dasRaw);

	dasRaw->uuid = uuid;
	dasRaw->RawDataUnit = rawDataUnit;
	dasRaw->StartLocusIndex = startLocusIndex;
	dasRaw->NumberOfLoci = numberOfLoci;

	if (!rawDescription.empty()) {
		dasRaw->RawDescription = soap_new_std__string(soapContext, 1);
		dasRaw->RawDescription->assign(rawDescription);
	}

	// Das time array XML
	dasRaw->RawDataTime = soap_new_prodml2__DasTimeArray(soapContext, 1);
	dasRaw->RawDataTime->__DasTimeArray_sequence = soap_new___prodml2__DasTimeArray_sequence(soapContext, 1);
	dasRaw->RawDataTime->__DasTimeArray_sequence->StartTime = startTime;
	dasRaw->RawDataTime->__DasTimeArray_sequence->EndTime = gsoap_eml2_1::soap_new_std__string(soapContext, 1);
	dasRaw->RawDataTime->__DasTimeArray_sequence->EndTime->assign(endTime);
	dasRaw->RawDataTime->__DasTimeArray_sequence->TimeArray = soap_new_eml21__IntegerExternalArray(soapContext, 1);
	dasRaw->RawDataTime->__DasTimeArray_sequence->TimeArray->NullValue = -1;
	dasRaw->RawDataTime->__DasTimeArray_sequence->TimeArray->Values = soap_new_eml21__ExternalDataset(soapContext, 1);
	eml21__ExternalDatasetPart* edp = soap_new_eml21__ExternalDatasetPart(soapContext, 1);
	dasRaw->RawDataTime->__DasTimeArray_sequence->TimeArray->Values->ExternalFileProxy.push_back(edp);
	edp->StartIndex = 0;
	edp->Count = timeCount;
	edp->PathInExternalFile = "/Acquisition/Raw[0]/RawDataTime";
	edp->EpcExternalPartReference = proxy->newEmlReference();

	// Das data array XML
	dasRaw->RawData = soap_new_prodml2__DasRawData(soapContext, 1);
	dasRaw->RawData->Dimensions.push_back(slowestHdfDimension);
	dasRaw->RawData->Dimensions.push_back(fastestHdfDimension);
	if (datatypeIsInteger) {
		eml21__IntegerExternalArray* xmlArray = soap_new_eml21__IntegerExternalArray(soapContext, 1);
		dasRaw->RawData->RawDataArray = xmlArray;
		xmlArray->Values = soap_new_eml21__ExternalDataset(soapContext, 1);
		xmlArray->NullValue = (numeric_limits<LONG64>::min)();
		edp = soap_new_eml21__ExternalDatasetPart(soapContext, 1);
		xmlArray->Values->ExternalFileProxy.push_back(edp);
	}
	else {
		eml21__FloatingPointExternalArray* xmlArray = soap_new_eml21__FloatingPointExternalArray(soapContext, 1);
		dasRaw->RawData->RawDataArray = xmlArray;
		xmlArray->Values = soap_new_eml21__ExternalDataset(soapContext, 1);
		edp = soap_new_eml21__ExternalDatasetPart(soapContext, 1);
		xmlArray->Values->ExternalFileProxy.push_back(edp);
	}
	edp->StartIndex = 0;
	edp->Count = timeCount * da->NumberOfLoci;
	edp->PathInExternalFile = "/Acquisition/Raw[0]/RawData";
	edp->EpcExternalPartReference = proxy->newEmlReference();

	return dasRaw;
}

void DasAcquisition::pushBackRaw(const std::string & guid, bool datatypeIsInteger, const char & datatypeByteCount, const std::string & rawDataUnit, LONG64* timeArray, const ULONG64 & timeCount, COMMON_NS::AbstractHdfProxy* proxy)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);

	prodml2__DasRaw* dasRaw = pushBackRawXmlOnly(!guid.empty() ? guid : GuidTools::generateUidAsString(),
		rawDataUnit, da->StartLocusIndex, da->NumberOfLoci, "",
		timeTools::convertMicrosecondUnixTimestampToIso(timeArray[0]), timeTools::convertMicrosecondUnixTimestampToIso(timeArray[timeCount - 1]), timeCount,
		prodml2__DasDimensions__time, prodml2__DasDimensions__locus,
		datatypeIsInteger, proxy);

	soap* soapContext = getGsoapContext();

	// Das time array HDF
	unsigned long long dataTimeDim = timeCount;
	proxy->writeArrayNd("/Acquisition/Raw[0]", "RawDataTime", H5T_NATIVE_LLONG, timeArray, &dataTimeDim, 1);
	std::vector<std::string> attributeNames;
	attributeNames.push_back("StartTime");
	attributeNames.push_back("EndTime");
	std::vector<std::string> attributeStringValues;
	attributeStringValues.push_back(dasRaw->RawDataTime->__DasTimeArray_sequence->StartTime);
	attributeStringValues.push_back(*dasRaw->RawDataTime->__DasTimeArray_sequence->EndTime);
	proxy->writeDatasetAttributes("/Acquisition/Raw[0]/RawDataTime", attributeNames, attributeStringValues);
	attributeNames.clear();
	attributeNames.push_back("StartIndex");
	attributeNames.push_back("Count");
	std::vector<int> attributeIntegerValues;
	attributeIntegerValues.push_back(0);
	attributeIntegerValues.push_back(timeCount);
	proxy->writeDatasetAttributes("/Acquisition/Raw[0]/RawDataTime", attributeNames, attributeIntegerValues);

	// Das data array HDF
	unsigned long long dataDims[2] = { timeCount, da->NumberOfLoci };
	int hdfDatatype = 0;
	if (datatypeIsInteger) {
		switch (datatypeByteCount) {
			case 1 : hdfDatatype = H5T_NATIVE_CHAR; break;
			case 2 : hdfDatatype = H5T_NATIVE_SHORT; break;
			case 4 : hdfDatatype = H5T_NATIVE_INT; break;
			case 8 : hdfDatatype = H5T_NATIVE_LLONG; break;
			default : throw invalid_argument("The raw datatype is not supported.");
		}
	}
	else {
		switch (datatypeByteCount) {
			case 4 : hdfDatatype = H5T_NATIVE_FLOAT; break;
			case 8 : hdfDatatype = H5T_NATIVE_DOUBLE; break;
			default : throw invalid_argument("The raw datatype is not supported.");
		}
	}
	proxy->createArrayNd("/Acquisition/Raw[0]", "RawData", hdfDatatype, dataDims, 2);
	attributeStringValues.clear();
	attributeStringValues.push_back(soap_prodml2__DasDimensions2s(soapContext,dasRaw->RawData->Dimensions[0]));
	attributeStringValues.push_back(soap_prodml2__DasDimensions2s(soapContext, dasRaw->RawData->Dimensions[1]));
	proxy->writeDatasetAttribute("/Acquisition/Raw[0]/RawData", "Dimensions", attributeStringValues);
	attributeNames.clear();
	attributeNames.push_back("StartIndex");
	attributeNames.push_back("Count");
	attributeIntegerValues.clear();
	attributeIntegerValues.push_back(0);
	attributeIntegerValues.push_back(timeCount * da->NumberOfLoci);
	proxy->writeDatasetAttributes("/Acquisition/Raw[0]/RawData", attributeNames, attributeIntegerValues);
	
	//init Raw Group Hdf Attributes
	attributeNames.clear();
	attributeNames.push_back("uuid");
	attributeNames.push_back("RawDataUnit");

	attributeStringValues.clear();
	attributeStringValues.push_back(dasRaw->uuid);
	attributeStringValues.push_back(dasRaw->RawDataUnit);

	proxy->writeGroupAttributes("/Acquisition/Raw[0]", attributeNames, attributeStringValues);

	attributeNames.clear();
	attributeNames.push_back("NumberOfLoci");
	attributeNames.push_back("StartLocusIndex");

	attributeIntegerValues.clear();
	attributeIntegerValues.push_back(dasRaw->NumberOfLoci);
	attributeIntegerValues.push_back(dasRaw->StartLocusIndex);

	proxy->writeGroupAttributes("/Acquisition/Raw[0]", attributeNames, attributeIntegerValues);

	//init Acquisition Group Hdf Attributes
	if (da->Raw.size() + da->Calibration.size() + (da->Processed == nullptr ? 0 : da->Processed->Fbe.size() + da->Processed->Spectra.size()) == 1) {
		initHdfAttributes();
	}
}

#define COMMON_CODE_WRITE_INTO_DATASET _prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1); \
	hsize_t numValuesInEachDimension[] = {numSampleForAllLoci, da->NumberOfLoci}; \
	hsize_t offsetInEachDimension[] = {timeStepIndex, 0}; \
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();

void DasAcquisition::writeIntoDataset(float * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_FLOAT, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

void DasAcquisition::writeIntoDataset(double * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_DOUBLE, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

void DasAcquisition::writeIntoDataset(LONG64 * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_LLONG, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

void DasAcquisition::writeIntoDataset(int * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_INT, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

void DasAcquisition::writeIntoDataset(short * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_SHORT, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

void DasAcquisition::writeIntoDataset(char * data,
	unsigned long numSampleForAllLoci,
	unsigned long timeStepIndex)
{
	COMMON_CODE_WRITE_INTO_DATASET
	hdfProxy->writeArrayNdSlab("/Acquisition/Raw[0]", "RawData", H5T_NATIVE_CHAR, data, numValuesInEachDimension, offsetInEachDimension, 2);
}

std::string DasAcquisition::getJobUuid() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->AcquisitionId; }
std::string DasAcquisition::getFacilityUuid() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->FacilityId.empty() ? string() : static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->FacilityId[0]; }
std::string DasAcquisition::getVendorName() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->VendorCode->Name; }

double DasAcquisition::getPulseRate() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->PulseRate->__item; }
gsoap_eml2_1::eml21__FrequencyUom DasAcquisition::getPulseRateUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->PulseRate->uom; }

double DasAcquisition::getPulseWidth() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->PulseWidth->__item; }
gsoap_eml2_1::eml21__TimeUom DasAcquisition::getPulseWidthUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->PulseWidth->uom; }

double DasAcquisition::getGaugeLength() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->GaugeLength->__item; }
gsoap_eml2_1::eml21__LengthUom DasAcquisition::getGaugeLengthUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->GaugeLength->uom; }

double DasAcquisition::getSpatialSamplingInterval() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->SpatialSamplingInterval->__item; }
gsoap_eml2_1::eml21__LengthUom DasAcquisition::getSpatialSamplingIntervalUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->SpatialSamplingInterval->uom; }

double DasAcquisition::getMinimumFrequency() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->MinimumFrequency->__item; }
gsoap_eml2_1::eml21__FrequencyUom DasAcquisition::getMinimumFrequencyUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->MinimumFrequency->uom; }

double DasAcquisition::getMaximumFrequency() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->MaximumFrequency->__item; }
gsoap_eml2_1::eml21__FrequencyUom DasAcquisition::getMaximumFrequencyUom() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->MaximumFrequency->uom; }

ULONG64 DasAcquisition::getLociCount() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->NumberOfLoci; }
LONG64 DasAcquisition::getStartLocusIndex() const { 
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->StartLocusIndex <= (numeric_limits<LONG64>::max)() ? da->StartLocusIndex : static_cast<LONG64>(da->StartLocusIndex);
}

std::string DasAcquisition::getMeasurementStartIsoTime() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->MeasurementStartTime; }

bool DasAcquisition::isTriggeredMeasurement() const { return static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1)->TriggeredMeasurement; }

unsigned int DasAcquisition::getRawCount() const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw.size();
}

gsoap_eml2_1::prodml2__DasDimensions DasAcquisition::getRawDataSlowestDimension(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->RawData->Dimensions[0];
}

gsoap_eml2_1::prodml2__DasDimensions DasAcquisition::getRawDataFastestDimension(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->RawData->Dimensions[1];
}

std::string DasAcquisition::getRawDataUnit(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->RawDataUnit;
}

LONG64 DasAcquisition::getStartLocusIndex(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->StartLocusIndex <= (numeric_limits<LONG64>::max)() ? da->Raw[rawIndex]->StartLocusIndex : static_cast<LONG64>(da->Raw[rawIndex]->StartLocusIndex);
}

ULONG64 DasAcquisition::getNumberOfLoci(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->NumberOfLoci;
}

ULONG64 DasAcquisition::getRawDataTimeCount(const unsigned int & rawIndex) const
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	return da->Raw[rawIndex]->RawDataTime->__DasTimeArray_sequence->TimeArray->Values->ExternalFileProxy[0]->Count;
}

RESQML2_NS::AbstractValuesProperty::hdfDatatypeEnum DasAcquisition::getRawDataHdfDatatype(const unsigned int & rawIndex) const
{
	COMMON_NS::AbstractHdfProxy* hdfProxy = getHdfProxy();

	hid_t dt = -1;
	if (gsoapProxy2_1 != nullptr) {
		_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);

		if (da->Raw[rawIndex]->RawData->RawDataArray->soap_type() == SOAP_TYPE_gsoap_eml2_1_eml21__FloatingPointExternalArray) {
			dt = hdfProxy->getHdfDatatypeInDataset(static_cast<eml21__FloatingPointExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray)->Values->ExternalFileProxy[0]->PathInExternalFile);
		}
		else if (da->Raw[rawIndex]->RawData->RawDataArray->soap_type() == SOAP_TYPE_gsoap_eml2_1_eml21__IntegerExternalArray) {
			dt = hdfProxy->getHdfDatatypeInDataset(static_cast<eml21__IntegerExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray)->Values->ExternalFileProxy[0]->PathInExternalFile);
		}
		else {
			return RESQML2_NS::AbstractValuesProperty::UNKNOWN;
		}
	}
	else {
		throw logic_error("Not implemented yet");
	}

	if (H5Tequal(dt, H5T_NATIVE_DOUBLE) > 0)
		return RESQML2_NS::AbstractValuesProperty::DOUBLE;
	else if (H5Tequal(dt, H5T_NATIVE_FLOAT) > 0)
		return RESQML2_NS::AbstractValuesProperty::FLOAT;
	else if (H5Tequal(dt, H5T_NATIVE_LLONG) > 0)
		return RESQML2_NS::AbstractValuesProperty::LONG;
	else if (H5Tequal(dt, H5T_NATIVE_ULLONG) > 0)
		return RESQML2_NS::AbstractValuesProperty::ULONG;
	else if (H5Tequal(dt, H5T_NATIVE_INT) > 0)
		return RESQML2_NS::AbstractValuesProperty::INT;
	else if (H5Tequal(dt, H5T_NATIVE_UINT) > 0)
		return RESQML2_NS::AbstractValuesProperty::UINT;
	else if (H5Tequal(dt, H5T_NATIVE_SHORT) > 0)
		return RESQML2_NS::AbstractValuesProperty::SHORT;
	else if (H5Tequal(dt, H5T_NATIVE_USHORT) > 0)
		return RESQML2_NS::AbstractValuesProperty::USHORT;
	else if (H5Tequal(dt, H5T_NATIVE_CHAR) > 0)
		return RESQML2_NS::AbstractValuesProperty::CHAR;
	else if (H5Tequal(dt, H5T_NATIVE_UCHAR) > 0)
		return RESQML2_NS::AbstractValuesProperty::UCHAR;

	return RESQML2_NS::AbstractValuesProperty::UNKNOWN; // unknwown datatype...
}

void DasAcquisition::getRawDataAsDoubleValues(const unsigned int & rawIndex, double * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__FloatingPointExternalArray* hdfValues = static_cast<eml21__FloatingPointExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfDoubleValues(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataAsFloatValues(const unsigned int & rawIndex, float * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__FloatingPointExternalArray* hdfValues = static_cast<eml21__FloatingPointExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfFloatValues(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataAsLongValues(const unsigned int & rawIndex, LONG64 * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__IntegerExternalArray* hdfValues = static_cast<eml21__IntegerExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfGSoapLong64Values(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataAsIntValues(const unsigned int & rawIndex, int * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__IntegerExternalArray* hdfValues = static_cast<eml21__IntegerExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfIntValues(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataAsShortValues(const unsigned int & rawIndex, short * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__IntegerExternalArray* hdfValues = static_cast<eml21__IntegerExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfShortValues(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataAsCharValues(const unsigned int & rawIndex, char * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__IntegerExternalArray* hdfValues = static_cast<eml21__IntegerExternalArray*>(da->Raw[rawIndex]->RawData->RawDataArray);

	getHdfProxy()->readArrayNdOfCharValues(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}

void DasAcquisition::getRawDataTime(const unsigned int & rawIndex, LONG64 * values)
{
	_prodml2__DasAcquisition* da = static_cast<_prodml2__DasAcquisition*>(gsoapProxy2_1);
	eml21__IntegerExternalArray* hdfValues = da->Raw[rawIndex]->RawDataTime->__DasTimeArray_sequence->TimeArray;

	getHdfProxy()->readArrayNdOfGSoapLong64Values(hdfValues->Values->ExternalFileProxy[0]->PathInExternalFile, values);
}


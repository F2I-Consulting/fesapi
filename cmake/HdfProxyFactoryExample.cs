using f2i.energisticsStandardsApi.${FESAPI_COMMON_NS};

namespace example
{
    public class HdfProxyFactoryExample : HdfProxyFactory
    {
        public override f2i.energisticsStandardsApi.${FESAPI_EML2_NS}.AbstractHdfProxy make(DataObjectRepository repo, string guid, string title, 
            string packageDirAbsolutePath, string externalFilePath, 
            DataObjectRepository.openingMode hdfPermissionAccess)
        {
            return new HdfProxyExample(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
        }
    }
}

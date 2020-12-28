using F2iConsulting.Fesapi.${FESAPI_COMMON_NS};

namespace example
{
    public class HdfProxyFactoryExample : HdfProxyFactory
    {
        public override F2iConsulting.Fesapi.${FESAPI_EML2_NS}.AbstractHdfProxy make(DataObjectRepository repo, string guid, string title, 
            string packageDirAbsolutePath, string externalFilePath, 
            DataObjectRepository.openingMode hdfPermissionAccess)
        {
            return new HdfProxyExample(repo, guid, title, packageDirAbsolutePath, externalFilePath, hdfPermissionAccess);
        }
    }
}

#include <list>
#include <map>
#include <string>
#include <memory>
#include <utility>

/**
* This is the actual asset object
*/
class Asset
{
	
};

//This is a proxy calss to store the asset regystry data
class AssetData
{
	uint64_t m_UID;
	std::string m_path;
	bool m_loaded;

	/**
	 * \brief Generates a new UID for each call
	 * \return Unique ID
	*/
	static uint64_t GenerateId()
	{
		static uint64_t count = 0;
		return ++count;
	}
	
public:
	AssetData(const std::string& path) :m_path(path), m_loaded(false)
	{
		m_UID = GenerateId();
	}

	AssetData(const std::string& path, const uint64_t& UID) :m_UID(UID), m_path(path), m_loaded(false) {}

	//Actually loads in the asset
	Asset GetAsset();
	std::string GetPath();
	int GetUID();
};

/** Holds the complleate list of registered assets.
* Loads the list at startup
* Loades the actual asset data when asked
* Unloads when asked, or new bundle is loaded
*/
class AssetManager
{
	std::map<int, std::unique_ptr<AssetData>> assetRegistry;
	
	void LoadAssetDatabase()
	{
		
	}

public:
	AssetManager()
	{
		LoadAssetDatabase();
	}

	std::unique_ptr<AssetData>& FindAsset(std::string path)
	{
		for (auto& asset : assetRegistry)
		{
			if(asset.second->GetPath() == path)
			{
				return asset.second;
			}
		}
	}
};



void main1()
{
	AssetManager a();
	
}
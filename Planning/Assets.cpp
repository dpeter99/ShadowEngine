#include <list>
#include <map>
#include <string>
#include <memory>
#include <utility>

class Asset
{
	
};

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
	AssetData(std::string path) :m_path(std::move(path)), m_loaded(false)
	{
		m_UID = GenerateId();
	}

	AssetData(std::string path, const uint64_t& UID) :m_UID(UID), m_path(std::move(path)), m_loaded(false) {}

	//Actually loads in the asset
	Asset GetAsset();
	std::string GetPath();
	int GetUID();
};

class AssetManager
{
	std::map<int, std::shared_ptr<AssetData>> assetRegistry;
	
	void LoadAssetDatabase()
	{
		std::unique_ptr<AssetData> a = std::make_unique<AssetData>("./Texture/test");
	}

public:
	AssetManager()
	{
		LoadAssetDatabase();
	}

	std::shared_ptr<AssetData> FindAsset(std::string path)
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



void main()
{
	AssetManager a();
	
}
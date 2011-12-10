/*
 * SimpleCache.h
 *
 * Created by: Dr. Strangecode
 * ---------------------------------------------
 * This is free code, it can be used, modified, 
 * destroyed, raped and whatever without limits.
 * I own no copyrights over it.
 * This code is provided AS IS without warranty
 * of any kind either expressed or implied, 
 * including but not limited to the implied 
 * warranties of merchantability and/or fitness 
 * for a particular purpose.
 * ---------------------------------------------
 * For more free code visit http://drstrangecode.org
 */

#ifndef SIMPLECACHE_H_
#define SIMPLECACHE_H_

#include <FGraphics.h>
#include <FMedia.h>
#include <FBase.h>
#include <FIo.h>

/**
 * \brief A simple cache to store files in the application's Home directory
 *
 * This cache stores file inside the app's /Home directory
 * mapping them to a unique integer identifier.
 *
 * Multiple caches can be created, every instance of this class must
 * be constructed with a unique string name, a corresponding subdirectory
 * is then created inside the cache.
 *
 * */

namespace DSBadaUtilityLib {

class SimpleCache {
public:
	SimpleCache();
	virtual ~SimpleCache();

public:
	/**
	 * Constructs the object, always call Construct() before using the cache
	 * @param Osp::Base::String & cacheName a unique name for the cache
	 * */
	result Construct(Osp::Base::String & cacheName);

	/**
	 * Retrieves a specific file from the cache
	 * @param[in] int index the index of the file to retrieve
	 * @param[out] a ByteBuffer containing the corresponding data
	 * @return true if the file has been found, false otherwise
	 *
	 * */
	virtual bool GetFileForIndex(int index, Osp::Base::ByteBuffer & data);

	/**
	 * Stores an image inside the cache
	 * @param[in] Osp::Base::ByteBuffer & data the data to store
	 * @param[in] int index the index for mapping this bitmap inside the cache
	 * @return true if the operation succeded, false otherwise
	 * */
	virtual bool StoreFile(Osp::Base::ByteBuffer & data, int index);

	/**
	 * Deletes all the stored files inside the cache
	 * */
	virtual bool EmptyCache();

private:

	void BuildPathForCacheDirectory(Osp::Base::String &dirPath);
	void BuildPathForFileInCache(int index, Osp::Base::String &filePath);
	bool CreateCacheDirectory();
	bool DeleteCacheDirectory();

	Osp::Base::String _cacheName;

};

} // namespace

#endif /* SIMPLECACHE_H_ */

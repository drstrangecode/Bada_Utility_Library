/*
 * SimpleCache
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

#include "Cache/SimpleCache.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Graphics;
using namespace Osp::Io;

namespace DSBadaUtilityLib {

SimpleCache::SimpleCache() {

}

SimpleCache::~SimpleCache() {

}

result SimpleCache::Construct(String & cacheName) {
	_cacheName = cacheName;

	String cacheDirPath;
	BuildPathForCacheDirectory(cacheDirPath);
	if (!File::IsFileExist(cacheDirPath)) {
		CreateCacheDirectory();
	}

	return E_SUCCESS;
}

bool SimpleCache::GetFileForIndex(int index, ByteBuffer & data) {

	String filePath;
	BuildPathForFileInCache(index, filePath);

	if (!File::IsFileExist(filePath)) {
		return false;
	}

	AppLog("Reading data from cached file at %S", filePath.GetPointer());

	File cachedFile;
	cachedFile.Construct(filePath, L"r+");
	if (IsFailed(GetLastResult())) {
		AppLog("Error opening destination file in cache");
		return false;
	}

	FileAttributes fAttributes;
	File::GetAttributes(filePath, fAttributes);

	data.Construct(fAttributes.GetFileSize());
	cachedFile.Read(data);
	AppLog("Read cache: %d bytes", data.GetCapacity());
	if (IsFailed(GetLastResult())) {
		AppLog("Error reading from cached file");
		return false;
	}

	return true;

}

bool SimpleCache::StoreFile(ByteBuffer & data, int position) {

	String filePath;
	BuildPathForFileInCache(position, filePath);

	AppLog("Storing data object in file at %S", filePath.GetPointer());

	File cachedFile;
	cachedFile.Construct(filePath, L"w+");
	if (IsFailed(GetLastResult())) {
		AppLog("Error opening destination file in cache");
		return false;
	}

	cachedFile.Write(data);
	if (IsFailed(GetLastResult())) {
		AppLog("Error writing data to destination file in cache");
		return false;
	}

	return true;

}

bool SimpleCache::EmptyCache() {
	if (DeleteCacheDirectory() && CreateCacheDirectory()) {
		return true;
	}
	else {
		return false;
	}
}

void SimpleCache::BuildPathForCacheDirectory(Osp::Base::String &dirPath) {
	dirPath = L"/Home";
	dirPath.Append("/");
	dirPath.Append(_cacheName);
}

void SimpleCache::BuildPathForFileInCache(int index, String &filePath) {
	BuildPathForCacheDirectory(filePath);
	filePath.Append("/");
	filePath.Append(index);
}

bool SimpleCache::CreateCacheDirectory() {
	String cacheDirPath;
	BuildPathForCacheDirectory(cacheDirPath);
	result r = Directory::Create(cacheDirPath, false);
	if (IsFailed(r)) {
		AppLog("Cannot create cache directory, aborting...");
		return false;
	}

	return true;
}

bool SimpleCache::DeleteCacheDirectory() {
	String cacheDirPath;
	BuildPathForCacheDirectory(cacheDirPath);
	result r = Directory::Remove(cacheDirPath, true);
	if (IsFailed(r)) {
		AppLog("Cannot delete cache directory, aborting...");
		return false;
	}

	return true;
}

} // namespace





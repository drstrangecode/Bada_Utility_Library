/*
 * SimpleFileDownloaderThread.cpp
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

#include "Download/SimpleFileDownloaderThread.h"

using namespace Osp::Content;
using namespace Osp::Base;
using namespace Osp::Base::Utility;
using namespace Osp::Base::Runtime;
using namespace Osp::Base::Collection;
using namespace Osp::Ui::Controls;

namespace DSBadaUtilityLib {

SimpleFileDownloaderThread::SimpleFileDownloaderThread() {

}

SimpleFileDownloaderThread::~SimpleFileDownloaderThread() {

}

result SimpleFileDownloaderThread::Construct(Form * listenerForm) {
	_listenerForm = listenerForm;
	return Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
}

bool SimpleFileDownloaderThread::OnStart(void) {
	AppLog("ImagesDownloaderThread starting");

	contentTransfer = new ContentTransfer();
	contentTransfer->Construct(*this);
	requestsMap.Construct();

	return true;
}

void SimpleFileDownloaderThread::OnStop(void) {
	AppLog("ImagesDownloaderThread terminating");

	/* Cancel all active downloads */
	contentTransfer->CancelAll();

	/* Cancel all pending downloads */
	contentTransfer->RemoveAll();

	/* delete the object */
	delete contentTransfer;

}

ArrayList * SimpleFileDownloaderThread::BuildArgumentsListForDownloadN(Osp::Base::String & fileUrl, int index) {

	String * imageUrl = new String(fileUrl);
	Integer * position = new Integer(index);

	ArrayList * args = new ArrayList();
	args->Construct();
	args->Add(*imageUrl);
	args->Add(*position);

	return args;
}

void SimpleFileDownloaderThread::OnUserEventReceivedN(RequestId requestId, IList * pArgs) {

	if (requestId == USER_EVENT_DOWNLOAD_FILE) {

		String * imageUrl = static_cast<String *>(pArgs->GetAt(0));
		Integer * position = static_cast<Integer *>(pArgs->GetAt(1));

		Uri uri;
		uri.SetUri(*imageUrl);

		long reqId;
		contentTransfer->DownloadToBuffer(uri, reqId, 0, 0);
		Long * requestId = new Long(reqId);
		Integer * positionIndex = new Integer(*position);
		requestsMap.Add(*requestId, *positionIndex);

		/* Delete the arguments list */
		pArgs->RemoveAll(true);
		delete pArgs;
	}

}

void SimpleFileDownloaderThread::OnContentTransferInProgress(RequestId requestID, int totalReceivedSize) {

}

void SimpleFileDownloaderThread::OnContentUploadCompleted(RequestId requestID, result res,
		const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMessage) {


}

void SimpleFileDownloaderThread::OnContentDownloadCompleted(RequestId requestID,
		Osp::Content::ContentId contentID, result res,
		const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMessage) {

}

void SimpleFileDownloaderThread::OnContentDownloadToBufferCompleted(RequestId reqId,
		Osp::Base::ByteBuffer* pBuffer, result r,
		const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMessage) {

	Long * requestId = new Long(reqId);

	/* Retrieve the position */
	int position = static_cast<Integer *>(requestsMap.GetValue(*requestId))->ToInt();

	/* Remove the pair from the hashmap */
	requestsMap.Remove(*requestId, true);
	delete requestId;

	if (pBuffer == null) {
		AppLog("pBuffer is null, no image downloaded: %S", errorMessage.GetPointer());
		return;
	}

	/* Retrieve and copy the data buffer */
	ByteBuffer* imageBuffer = new ByteBuffer();
	imageBuffer->Construct(pBuffer->GetLimit());
	imageBuffer->SetLimit(pBuffer->GetLimit());
	imageBuffer->CopyFrom(*pBuffer);

	/* Build the parameters list */
	ArrayList * params = new ArrayList();
	params->Construct();
	params->Add(*new Integer(position));
	params->Add(*imageBuffer);

	_listenerForm->SendUserEvent(USER_EVENT_FILE_DOWNLOADED, params);


}

void SimpleFileDownloaderThread::OnDownloadDescriptorReceived(RequestId requestID,
		const Osp::Content::DownloadDescriptor& description) {

}

void SimpleFileDownloaderThread::OnContentTransferCanceled(RequestId reqId, result res,
		const Osp::Base::String& errorCode,
		const Osp::Base::String& errorMessage) {

	Long * requestId = new Long(reqId);
	/* Remove the pair from the hashmap */
	requestsMap.Remove(*requestId, true);

}

} // namespace

/*
 * SimpleFileDownloaderThread.h
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

#ifndef SIMPLEFILEDOWNLOADERTHREAD_H_
#define SIMPLEFILEDOWNLOADERTHREAD_H_

#include <FBase.h>
#include <FContent.h>
#include <FUi.h>

/**
 * \brief Main namespace for accessing the library code
 * */
namespace DSBadaUtilityLib {

/**
 * \brief A thread used to download files asynchronously, and send them to a listener form.
 *        Typically used to lazy load images inside a ListView. But not only.
 *
 * This class uses the Bada ContentTransfer APIs in order to download
 * one ore more files simultaneously via HTTP GET.
 * Communication with this thread is achieved through the SendUserEvent() API.
 * User events are:<br>
 * <strong>USER_EVENT_DOWNLOAD_FILE</strong> used by the outside world to start a download, the IList of parameters
 * must contain the file url and an integer index that will be passed back to the caller once the file
 * has been downloaded.<br>
 *
 * <code>
 *      String imageUrl = String("http://somewere.com/image.jpg");
 *
 *      ArrayList * args = fileDownloaderThread.BuildArgumentsListForDownloadN(imageUrl, 1);
 *		fileDownloaderThread.SendUserEvent(SimpleFileDownloaderThread::USER_EVENT_DOWNLOAD_IMAGE, args);
 * </code>
 *
 * \see BuildArgumentsListForDownloadN()
 *
 * <strong>USER_EVENT_FILE_DOWNLOADED</strong> sent by this thread to the listener form once the file has been downloaded,
 * the provided IList of args contains in sequence:<ol>
 * <li>The index passed as input when the download was started</li>
 * <li>The data buffer in form of a ByteBuffer *</li>
 * </ol>
 *	Here's what the listener form must do in order to retrieve the downloaded data,
 *	in the case of JPEG images.<br>
 * <pre>
 * void MainForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs) {
 *
 * 	if (requestId == ImagesDownloaderThread::USER_EVENT_FILE_DOWNLOADED) {
 *
 * 		Integer * index = static_cast<Integer *>(pArgs->GetAt(0));
 * 		ByteBuffer * dataBuffer = static_cast<ByteBuffer *>(pArgs->GetAt(1));
 *
 * 		Image * image = new Image();
 * 		image->Construct();
 * 		Bitmap * pBitmap = image->DecodeN(*dataBuffer, IMG_FORMAT_JPG, BITMAP_PIXEL_FORMAT_R8G8B8A8);
 * 		delete image;
 *
 * 		pArgs->RemoveAll(true);
 * 		delete pArgs;
 *
 * 	}
 * }
 * </pre>
 *
 * */

class SimpleFileDownloaderThread : public Osp::Base::Runtime::Thread,
                                   public Osp::Content::IContentTransferListener
{
public:
	SimpleFileDownloaderThread();
	virtual ~SimpleFileDownloaderThread();

	/**
	 * Constructs the object, call this method before starting the thread!
	 * @param Osp::Ui::Controls::Form * listenerForm The Bada Form that will be notified of downloaded images
	 * */
	result Construct(Osp::Ui::Controls::Form * listenerForm);

	virtual bool OnStart(void);
	virtual void OnStop(void);

	virtual Osp::Base::Collection::ArrayList * BuildArgumentsListForDownloadN(Osp::Base::String & fileUrl, int index);
	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs);

	/**
	 * The User Event sent TO this thread to start a download
	 * */
	static const int USER_EVENT_DOWNLOAD_FILE = 101;

	/**
	 * The User Event sent BY this thread to notify the listener form about completed downloads
	 * */
	static const int USER_EVENT_FILE_DOWNLOADED = 102;

public:
    void OnContentTransferInProgress(RequestId requestID, int totalReceivedSize);
    void OnContentUploadCompleted(RequestId requestID, result res, const Osp::Base::String& errorCode, const Osp::Base::String& errorMessage);
    void OnContentDownloadCompleted(RequestId requestID, Osp::Content::ContentId contentID, result res, const Osp::Base::String& errorCode, const Osp::Base::String& errorMessage);
    void OnContentDownloadToBufferCompleted(RequestId reqId, Osp::Base::ByteBuffer* pBuffer, result r, const Osp::Base::String& errorCode, const Osp::Base::String& errorMessage);
    void OnDownloadDescriptorReceived(RequestId requestID, const Osp::Content::DownloadDescriptor& description);
    void OnContentTransferCanceled(RequestId reqId, result res, const Osp::Base::String& errorCode, const Osp::Base::String& errorMessage);


private:
	Osp::Content::ContentTransfer * contentTransfer;
	Osp::Base::Collection::HashMap requestsMap;
	Osp::Ui::Controls::Form * _listenerForm;

};

} // namespace

#endif /* SIMPLEFILEDOWNLOADERTHREAD_H_ */


#include "DeckLinkAPI_h.h"

// The callback class is used for video input format detection in this example.
class DeckLinkKeyerDelegate : public IDeckLinkInputCallback
{
public:
	ULONG		m_refCount;

	~DeckLinkKeyerDelegate();
	DeckLinkKeyerDelegate();
//public:

	bool decklinkIsok;
	BMDDisplayMode currentDisplayMode;
	bool						displayModeDetected;
	IDeckLinkIterator		*deckLinkIterator;
	IDeckLink				*deckLink;
	IDeckLinkInput			*deckLinkInput;
	IDeckLinkOutput			*deckLinkOutput;
	IDeckLinkDisplayMode		*detectedDisplayMode;

	IDeckLinkMutableVideoFrame*	m_videoFrameGdi;
	//IDeckLinkVideoFrame* theFrame;

	int theFrameBMIsize;

	int						numDevices = 0;
	HRESULT					result;
	IDeckLinkAttributes		*deckLinkAttributes = NULL;
	HRESULT					attributeResult;
	BOOL					keyingSupported;
	BOOL					HDkeyingSupported;
	int						selectedMode = 0;

	int	OutputGraphic(IDeckLinkDisplayMode *deckLink);
	void GdiDraw(IDeckLinkVideoFrame* theFrame);
	int	CheckFormatDetect(IDeckLinkAttributes		*deckLinkAttributes);



	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, LPVOID *ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE  Release(void);

	// IDeckLinkInputCallback
	virtual HRESULT STDMETHODCALLTYPE VideoInputFormatChanged(BMDVideoInputFormatChangedEvents, IDeckLinkDisplayMode*, BMDDetectedVideoInputFormatFlags);
	virtual HRESULT STDMETHODCALLTYPE VideoInputFrameArrived(IDeckLinkVideoInputFrame*, IDeckLinkAudioInputPacket*);
};

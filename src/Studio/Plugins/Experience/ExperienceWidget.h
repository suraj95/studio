/****************************************************************************
**
** Copyright 2019 neuromore co
** Contact: https://neuromore.com/contact
**
** Commercial License Usage
** Licensees holding valid commercial neuromore licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and neuromore. For licensing terms
** and conditions see https://neuromore.com/licensing. For further
** information use the contact form at https://neuromore.com/contact.
**
** neuromore Public License Usage
** Alternatively, this file may be used under the terms of the neuromore
** Public License version 1 as published by neuromore co with exceptions as 
** appearing in the file neuromore-class-exception.md included in the 
** packaging of this file. Please review the following information to 
** ensure the neuromore Public License requirements will be met: 
** https://neuromore.com/npl
**
****************************************************************************/

#ifndef __NEUROMORE_EXPERIENCEWIDGET_H
#define __NEUROMORE_EXPERIENCEWIDGET_H

// include required headers
#include "../../Config.h"
#include <Core/EventHandler.h>
#include <QWidget>
#include <QMovie>
#include <QTimer>
#include <QBuffer>
#include <QNetworkReply>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPushButton>
#include <QHBoxLayout>
#include <Audio/MediaContent.h>

// OpenCV
#ifdef OPENCV_SUPPORT
#include "../../OpenCV/OpenCVVideoPlayer.h"
#endif

// for system master volume control
#ifdef NEUROMORE_PLATFORM_WINDOWS
	#include <endpointvolume.h>
#endif

class ExperienceWidget : public QWidget, public Core::EventHandler
{
	Q_OBJECT
	CORE_LOGDEBUG_DISABLE("ExperienceWidget", GetReadableType(), this);

	public:
		ExperienceWidget(QWidget* parent=NULL);
		virtual ~ExperienceWidget();

		void UpdateInterface();

		static void DrawPixmapKeepAspectRatio(QWidget* widget, QPainter& painter, const QPixmap& pixmap);

		// EVENTS ----------------------------------------------
		// experience events
		void OnExitStateReached(uint32 exitStatus) override;

		void OnPlayAudio(const char* url, int32 numLoops, double beginAt, double volume, bool allowStream) override;
		void OnStopAudio(const char* url) override;
		void OnSeekAudio(const char* url, uint32 millisecs) override;
		void OnPauseAudio(const char* url, bool unpause) override;

		void OnPlayVideo(const char* url, int32 numLoops, double beginAt, double volume, bool allowStream) override;
		void OnStopVideo() override;
		void OnSeekVideo(const char* url, uint32 millisecs) override;
		void OnPauseVideo(const char* url, bool unpause) override;

		void OnShowImage(const char* url) override;
		void OnHideImage() override;

		void OnShowText(const char* text, const Core::Color& color) override;
		void OnHideText() override;

		void OnSetBackgroundColor(const Core::Color& color) override;
		
		void OnSetFourZoneAVEColors(const float* red, const float* green, const float* blue, const float* alpha) override;
		void OnHideFourZoneAVE() override;

		void OnShowButton(const char* text, uint32 buttonId) override;
		void OnClearButtons() override;

		void OnActiveStateMachineChanged(StateMachine* stateMachine) override;
		
		// -----------------------------------------------------

		void SetVolume(float normalizedVolume, const char* filename);
		void SetGlobalVolume(float normalizedVolume);

		void SetPosition(float position, const char* filename);

		MediaContent* FindMediaContent(const char* filename);

		void Clear();

		// state transition button condition
		void AddButton(const char* text, uint32 buttonId);
		void ClearButtons();

		// clear animated gif
		void ClearAnimatedGif();

	private slots:
		void OnGifAnimationTimer();
		void OnRefreshTimer();

		void OnVideoLooped(QString url);

		void OnButtonClicked();

		 void ShowImage(QImage image);
		 void ShowImage(QPixmap pixmap);

		 void OnFinishedPreloading();

	private:
		void paintEvent(QPaintEvent* event) override;

		QNetworkAccessManager*		mNetworkAccessManager;
		Core::Array<MediaContent*>	mMediaContents;

		QTimer*						mRefreshTimer;

		void SetTimerEnabled(bool isEnabled);
		QTimer*						mGifTimer;
		QBuffer*					mGifBuffer;
		QMovie*						mGifMovie;
		
		QPixmap						mPixmap;
		QString						mText;
		QColor						mTextColor;

		QColor						mBackgroundColor;
		Core::Array<QColor>			mAVEZoneColors;

		Core::Array<QPushButton*>	mButtons;
		QHBoxLayout*				mButtonLayout;

		// .mp4 etc. movie
#ifdef OPENCV_SUPPORT
		QPixmap						mMoviePixmap;
		OpenCVVideoPlayer*			mVideoPlayer;
#endif

#ifdef NEUROMORE_PLATFORM_WINDOWS

		// windows master volume control
		void SetSystemMasterVolume(float normalizedVolume);
		IAudioEndpointVolume*		mEndpointVolume;

		// windows screen brightness controll via gamma ramp
		void SetScreenBrightness(double brightness);
		void SetScreenLSD (double micrograms);
		double mLastScreenBrightness;

		typedef BOOL (WINAPI *Type_SetDeviceGammaRamp)(HDC hDC, LPVOID lpRamp);
		HMODULE mGDI32;

		Type_SetDeviceGammaRamp mGetDeviceGammaRamp;
		Type_SetDeviceGammaRamp mSetDeviceGammaRamp;
		
		WORD mCurrentGammaArray[3][256];
		WORD mOriginalGammaArray[3][256];

#endif
};

#endif

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

#ifndef __NEUROMORE_ColorWheelNode_H
#define __NEUROMORE_ColorWheelNode_H

// include the required headers
#include "../Config.h"
#include "../Core/StandardHeaders.h"
#include "ProcessorNode.h"
#include "../DSP/ChannelProcessor.h"


class ENGINE_API ColorWheelNode : public ProcessorNode
{
	public:
		enum { TYPE_ID = 0x0055 };
		static const char* Uuid () { return "d5f155a2-f74d-11e5-9ce9-5e5517507c66"; }
		
		//
		enum
		{
			INPUTPORT_HUE	= 0,
			INPUTPORT_SAT	= 1,
			INPUTPORT_VAL	= 2,

			OUTPUTPORT_RED	= 0,
			OUTPUTPORT_GREEN= 1,
			OUTPUTPORT_BLUE	= 2,
		};

		// constructor & destructor
		ColorWheelNode(Graph* graph);
		~ColorWheelNode();

		// initialize & update
		void Init() override;
		void ReInit(const Core::Time& elapsed, const Core::Time& delta) override;
		void Start(const Core::Time& elapsed) override;
		void Update(const Core::Time& elapsed, const Core::Time& delta) override;

		void OnAttributesChanged() override;
		
		Core::Color GetColor() const override								{ return mColor; }
		uint32 GetType() const override											{ return TYPE_ID; }
		const char* GetTypeUuid() const override final							{ return Uuid(); }
		const char* GetReadableType() const override							{ return "Color Wheel"; }
		const char* GetRuleName() const override final							{ return "NODE_ColorWheel"; }
		uint32 GetPaletteCategory() const override								{ return CATEGORY_UTILS; }
		GraphObject* Clone(Graph* graph) override								{ ColorWheelNode* clone = new ColorWheelNode(graph); return clone; }

		const ChannelProcessor::Settings& GetSettings() override				{ return mSettings; }

	private:

		// main node color
		Core::Color			mColor;

		// settings for the node processor
		class ProcessorSettings : public ChannelProcessor::Settings
		{
			public:
				enum { TYPE_ID = 0x0055 };

				ProcessorSettings()			 {}
				virtual ~ProcessorSettings() {}
			
				uint32 GetType() const override		{ return TYPE_ID; }

				// Note: no settings for now, we'll add things like integral order later (requires ProcessorChain class)
		};
		
		ProcessorSettings	mSettings;

		// the node's channel processor
		class Processor : public ChannelProcessor
		{
			enum { TYPE_ID = 0x0055 };

			public:
				Processor() : ChannelProcessor()												{ Init(); }
				~Processor() { }

				uint32 GetType() const override													{ return TYPE_ID; }
				ChannelProcessor* Clone() override												{ Processor* clone = new Processor(); clone->Setup(mSettings); return clone; }

				// settings
				void Setup(const ChannelProcessor::Settings& settings) override					{ mSettings = static_cast<const ProcessorSettings&>(settings); }
				const Settings& GetSettings() const	override									{ return mSettings; }

				void Init() override
				{
					AddInput<double>();	 AddInput<double>();  AddInput<double>();
					AddOutput<double>(); AddOutput<double>(); AddOutput<double>();
				}

				void ReInit() override;
				void Update() override;

				const Core::Color& GetColor() const											{ return mColor; }

			private:
				ProcessorSettings		mSettings;
				Core::Color			mColor;					// the output color

		};
};


#endif

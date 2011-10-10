/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*
    This PVA_FF_QcelpSampleEntry Class is used for visual streams.
*/
#ifndef __QcelpSampleEntry_H__
#define __QcelpSampleEntry_H__

#include "sampleentry.h"
#include "qcelpatom.h"

class PVA_FF_QcelpSampleEntry : public PVA_FF_SampleEntry
{

    public:
        PVA_FF_QcelpSampleEntry(int32 codecType); // Constructor

        virtual ~PVA_FF_QcelpSampleEntry();

        // Member gets and sets

        uint16 getTimeScale()
        {
            return _timeScale;
        }
        void setTimeScale(uint16 ts)
        {
            _timeScale = ts;
        }
        void nextSampleSize(int32 size)
        {
        }
        // Rendering the PVA_FF_Atom in proper format (bitlengths, etc.) to an ostream
        virtual bool renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP *fp);


    private:
        virtual void recomputeSize();
        void init();

        // Reserved constants
        uint32 _reserved1[2]; // = { 0, 0 };
        uint16 _reserved2; // = 2;
        uint16 _reserved3; // = 16;
        uint32 _reserved4; // = 0;
        uint16 _reserved5; // = 0;

        uint16 _timeScale;
        PVA_FF_QcelpAtom *_pes;
};


#endif


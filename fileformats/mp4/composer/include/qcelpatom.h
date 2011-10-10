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
    This PVA_FF_QcelpAtom Class provides the offset between decoding
    time and composition time.
*/


#ifndef __QCELPAtom_H__
#define __QCELPAtom_H__

#include "atom.h"

class PVA_FF_QcelpDescriptor
{
public:
   PVA_FF_QcelpDescriptor():_vendor(), _decoder_version(0), _frames_per_sample(10){}
   ~PVA_FF_QcelpDescriptor(){}
   virtual bool renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP *fp);
   
public:
   void setFramesPerSample(uint8 frms) 
   {
       _frames_per_sample = frms;
   }   
   int32 getSize()
   {
       return 6;
   }

private:
   uint32 _vendor;
   uint8  _decoder_version;
   uint8  _frames_per_sample;
};
class PVA_FF_QcelpAtom : public PVA_FF_Atom
{

    public:
        PVA_FF_QcelpAtom(int32 streamType, int32 codecType); // Constructor

        virtual ~PVA_FF_QcelpAtom();


        // Rendering the PVA_FF_Atom in proper format (bitlengths, etc.) to an ostream
        virtual bool renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP *fp);

    private:
        void init();
        virtual void recomputeSize();

        PVA_FF_QcelpDescriptor * _pdescriptor;

};


#endif


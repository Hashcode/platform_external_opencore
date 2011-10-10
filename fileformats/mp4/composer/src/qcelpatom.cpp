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
    This PVA_FF_QCELPAtom Class provides the offset between decoding
    time and composition time.
*/


#define IMPLEMENT_QCELPAtom

#include "qcelpatom.h"
#include "a_atomdefs.h"
#include "atomutils.h"

// Constructor
PVA_FF_QcelpAtom::PVA_FF_QcelpAtom(int32 streamType, int32 codecType)
        : PVA_FF_Atom(FourCharConstToUint32('d','q','c','p'))
{

    PV_MP4_FF_NEW(fp->auditCB, PVA_FF_QcelpDescriptor, (), _pdescriptor);
  
    init();
    recomputeSize();
}

// Destructor
PVA_FF_QcelpAtom::~PVA_FF_QcelpAtom()
{
    // Cleanup the PVA_FF_ESDescriptor
    PV_MP4_FF_DELETE(NULL, PVA_FF_QcelpDescriptor, _pdescriptor);
}

// Rendering the PVA_FF_Atom in proper format (bitlengths, etc.) to an ostream
bool
PVA_FF_QcelpAtom::renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP *fp)
{
    int32 rendered = 0;

    if (!renderAtomBaseMembers(fp))
    {
        return false;
    }
    rendered += getDefaultSize();

    if (!_pdescriptor->renderToFileStream(fp))
    {
        return false;
    }
    rendered += _pdescriptor->getSize();

    return true;
}

void
PVA_FF_QcelpAtom::init()
{
    // Empty
}

void
PVA_FF_QcelpAtom::recomputeSize()
{
    _size = getDefaultSize() + _pdescriptor->getSize();

    // Update size of parent atom
    if (_pparent != NULL)
    {
        _pparent->recomputeSize();
    }
}

bool
PVA_FF_QcelpDescriptor::renderToFileStream(MP4_AUTHOR_FF_FILE_IO_WRAP *fp)
{
    if (!PVA_FF_AtomUtils::render32(fp, _vendor))
    {
        return false;
    }

    if (!PVA_FF_AtomUtils::render8(fp, _decoder_version))
    {
        return false;
    }
    if (!PVA_FF_AtomUtils::render8(fp, _frames_per_sample))
    {
        return false;
    }
    return true;
}


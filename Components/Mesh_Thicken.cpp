//
// Copyright (c) 2016 - 2017 Mesh Consultants Inc.
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//


#include "Mesh_Thicken.h"

#include <assert.h>

#include <Urho3D/Core/Context.h>
#include <Urho3D/Core/Object.h>
#include <Urho3D/Core/Variant.h>
#include <Urho3D/Container/Vector.h>
#include <Urho3D/Container/Str.h>

#include "ConversionUtilities.h"
#include "Geomlib_TriMeshThicken.h"
#include "TriMesh.h"

using namespace Urho3D;

String Mesh_Thicken::iconTexture = "Textures/Icons/Mesh_Thicken.png";

Mesh_Thicken::Mesh_Thicken(Context* context) : IoComponentBase(context, 2, 1)
{
	SetName("ThickenMesh");
	SetFullName("Thicken Triangle Mesh");
	SetDescription("Perform thickening operation on a triangle mesh");
	SetGroup(IoComponentGroup::MESH);
	SetSubgroup("Operators");

	inputSlots_[0]->SetName("Mesh");
	inputSlots_[0]->SetVariableName("M");
	inputSlots_[0]->SetDescription("Mesh to thicken");
	inputSlots_[0]->SetVariantType(VariantType::VAR_VARIANTMAP);
	inputSlots_[0]->SetDataAccess(DataAccess::ITEM);

	inputSlots_[1]->SetName("Width");
	inputSlots_[1]->SetVariableName("W");
	inputSlots_[1]->SetDescription("Width to thicken by");
	inputSlots_[1]->SetVariantType(VariantType::VAR_FLOAT);
	inputSlots_[1]->SetDataAccess(DataAccess::ITEM);
	inputSlots_[1]->SetDefaultValue(Variant(0.04f));
	inputSlots_[1]->DefaultSet();

	outputSlots_[0]->SetName("Mesh");
	outputSlots_[0]->SetVariableName("M");
	outputSlots_[0]->SetDescription("Mesh after thickening");
	outputSlots_[0]->SetVariantType(VariantType::VAR_VARIANTMAP);
	outputSlots_[0]->SetDataAccess(DataAccess::ITEM);
}

void Mesh_Thicken::SolveInstance(
	const Vector<Variant>& inSolveInstance,
	Vector<Variant>& outSolveInstance
)
{
	assert(inSolveInstance.Size() == inputSlots_.Size());
	assert(outSolveInstance.Size() == outputSlots_.Size());

	///////////////////
	// VERIFY & EXTRACT

	if (!IsAllInputValid(inSolveInstance)) {
		SetAllOutputsNull(outSolveInstance);
		return;
	}

	// Still need to verify input slot 0
	Variant meshIn = inSolveInstance[0];
	if (!TriMesh_Verify(meshIn)) {
		URHO3D_LOGWARNING("M must be a valid mesh.");
		outSolveInstance[0] = Variant();
		return;
	}
	float t = inSolveInstance[1].GetFloat();

	///////////////////
	// COMPONENT'S WORK

	Variant meshOut;
	bool success = Geomlib::TriMeshThicken(meshIn, t, meshOut);
	if (!success) {
		URHO3D_LOGWARNING("Thicken operation failed.");
		outSolveInstance[0] = Variant();
		return;
	}

	/////////////////
	// ASSIGN OUTPUTS

	outSolveInstance[0] = meshOut;
}
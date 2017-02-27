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


#pragma once

#include "IoComponentBase.h"
#include <Urho3D/Graphics/OctreeQuery.h>

class URHO3D_API Input_GeometryEdit : public IoComponentBase {

	URHO3D_OBJECT(Input_GeometryEdit, IoComponentBase)

public:
	Input_GeometryEdit(Urho3D::Context* context);

	static Urho3D::String iconTexture;

	virtual void PreLocalSolve();

	void SolveInstance(
		const Urho3D::Vector<Urho3D::Variant>& inSolveInstance,
		Urho3D::Vector<Urho3D::Variant>& outSolveInstance
	);

	Urho3D::Vector<int> trackedItems;
	int constraintFlags = 7;
	bool reset = true;

	Urho3D::RayQueryResult currentHitResult;

	void HandleMouseDown(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
	void HandleMouseMove(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);
	void HandleMouseUp(Urho3D::StringHash eventType, Urho3D::VariantMap& eventData);

	bool DoRaycast();
	int CreateEditGeometry(Urho3D::Variant geometry, float thickness, Urho3D::Color color);

	Urho3D::Vector3 GetConstrainedVector(Urho3D::Vector3 moveVec, int flags);
};
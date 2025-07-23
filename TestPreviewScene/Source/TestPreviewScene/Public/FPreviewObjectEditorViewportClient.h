

#pragma once


#include "CoreMinimal.h"
#include "EditorViewportClient.h"
#include "UPreviewObject.h"
#include "Engine/StaticMeshActor.h"

class TESTPREVIEWSCENE_API FPreviewObjectEditorViewportClient : public FEditorViewportClient
{
private:

	TObjectPtr<UPreviewObject> EditingPreviewObject;
	TOptional<AStaticMeshActor*> MeshActor;

public:
	FPreviewObjectEditorViewportClient(FEditorModeTools* InModeTools, FPreviewScene* InPreviewScene = nullptr, const TWeakPtr<SEditorViewport>& InEditorViewportWidget = nullptr);

	void SetEditingObject(UPreviewObject* PreviewObject);
	void OnAssetChanged();

	virtual void Tick(float DeltaSeconds) override;
};

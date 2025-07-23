

#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"
#include "AdvancedPreviewScene.h"

class UPreviewObject;
class FEditorViewportClient;
class TESTPREVIEWSCENE_API SPreviewObjectViewPort : public SEditorViewport
{
private:
	TSharedPtr<FAdvancedPreviewScene> PreviewScene;

public:
	SLATE_BEGIN_ARGS(SPreviewObjectViewPort)
		{
		}
	SLATE_ARGUMENT(UPreviewObject*, ManagedPreviewObject)

	SLATE_END_ARGS()

	TObjectPtr<UPreviewObject> ManagedPreviewObject;

	void Construct(const FArguments& InArgs);

	virtual void OnFocusViewportToSelection() override;
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;
	virtual TSharedPtr<SWidget> MakeViewportToolbar() override;
	/** End SViewport Interface */
};

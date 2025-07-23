


#include "SPreviewObjectViewPort.h"
#include "FPreviewObjectEditorViewportClient.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SPreviewObjectViewPort::Construct(const FArguments& InArgs)
{
	
	ManagedPreviewObject = InArgs._ManagedPreviewObject;
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

void SPreviewObjectViewPort::OnFocusViewportToSelection()
{
	SEditorViewport::OnFocusViewportToSelection();
}

TSharedRef<FEditorViewportClient> SPreviewObjectViewPort::MakeEditorViewportClient()
{
	FAdvancedPreviewScene::ConstructionValues ConstructionValues;
	ConstructionValues.LightBrightness = 4.0f;
	PreviewScene = MakeShareable(new FAdvancedPreviewScene(ConstructionValues));
	//PreviewScene->SetFloorVisibility(false);
	TSharedRef<FPreviewObjectEditorViewportClient> EditorViewportClient = MakeShareable(new FPreviewObjectEditorViewportClient(nullptr, PreviewScene.Get()));
	EditorViewportClient->SetEditingObject(ManagedPreviewObject.Get());
	return EditorViewportClient;
}

TSharedPtr<SWidget> SPreviewObjectViewPort::MakeViewportToolbar()
{
	return SEditorViewport::MakeViewportToolbar();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

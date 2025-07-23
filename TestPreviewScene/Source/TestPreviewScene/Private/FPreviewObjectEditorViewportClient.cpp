


#include "FPreviewObjectEditorViewportClient.h"

FPreviewObjectEditorViewportClient::FPreviewObjectEditorViewportClient(FEditorModeTools* InModeTools,
	FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget) : FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{
	// refresh the viewport real-time state
	SetRealtime(true);
}

void FPreviewObjectEditorViewportClient::SetEditingObject(UPreviewObject* PreviewObject)
{
	EditingPreviewObject = PreviewObject;

	// Bind the asset changed event to update the viewport when the asset changes
	EditingPreviewObject->OnAssetPropertyChanged.BindRaw(this, &FPreviewObjectEditorViewportClient::OnAssetChanged);
}

void FPreviewObjectEditorViewportClient::OnAssetChanged()
{
	if (EditingPreviewObject && EditingPreviewObject->StaticMesh)
	{
		if (!MeshActor.IsSet())
		{
			MeshActor = PreviewScene->GetWorld()->SpawnActor<AStaticMeshActor>(FVector::Zero(), FRotator::ZeroRotator);
			MeshActor.GetValue()->GetStaticMeshComponent()->SetStaticMesh(EditingPreviewObject->StaticMesh);
		}
		else
		{
			MeshActor.GetValue()->GetStaticMeshComponent()->SetStaticMesh(EditingPreviewObject->StaticMesh);
		}
		return;
	}
	if (MeshActor.IsSet())
	{
		MeshActor.GetValue()->Destroy();
	}
	MeshActor.Reset();
}

void FPreviewObjectEditorViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);
	PreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
}
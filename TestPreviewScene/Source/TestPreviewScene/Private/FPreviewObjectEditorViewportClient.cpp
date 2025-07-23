


#include "FPreviewObjectEditorViewportClient.h"

FPreviewObjectEditorViewportClient::FPreviewObjectEditorViewportClient(FEditorModeTools* InModeTools,
	FPreviewScene* InPreviewScene, const TWeakPtr<SEditorViewport>& InEditorViewportWidget) : FEditorViewportClient(InModeTools, InPreviewScene, InEditorViewportWidget)
{
	SetRealtime(true);
}

void FPreviewObjectEditorViewportClient::SetEditingObject(UPreviewObject* PreviewObject)
{
	EditingPreviewObject = PreviewObject;
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
void UPreviewObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if (OnAssetPropertyChanged.IsBound())
	{
		OnAssetPropertyChanged.Execute();
	}
}

#include "UPreviewObject.h"


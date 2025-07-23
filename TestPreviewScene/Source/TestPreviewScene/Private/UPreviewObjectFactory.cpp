


#include "UPreviewObjectFactory.h"
#include "UPreviewObject.h"

UPreviewObjectFactory::UPreviewObjectFactory()
{
	SupportedClass = UPreviewObject::StaticClass();
	bCreateNew = true;
}

bool UPreviewObjectFactory::CanCreateNew() const
{
	return true;
}

bool UPreviewObjectFactory::ShouldShowInNewMenu() const
{
	return true;
}

UObject* UPreviewObjectFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn)
{
	UPreviewObject* PreviewObject = NewObject<UPreviewObject>(InParent, InClass, InName, Flags);
	check(PreviewObject != nullptr);
	return PreviewObject;
}

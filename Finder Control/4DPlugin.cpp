/* --------------------------------------------------------------------------------
 #
 #	4DPlugin.c
 #	source generated by 4D Plugin Wizard
 #	Project : Finder Control
 #	author : miyako
 #	2014/08/06
 #
 # --------------------------------------------------------------------------------*/


#include "4DPluginAPI.h"
#include "4DPlugin.h"

#import <ScriptingBridge/ScriptingBridge.h>
#import "Finder.h"

FinderApplication *getFinder(){
	return [SBApplication applicationWithBundleIdentifier:@"com.apple.Finder"];
}

FinderItem *getFinderItem(C_TEXT &path){
	NSURL *url = path.copyUrl();
	FinderApplication *finder = getFinder();
	SBElementArray *items = [finder items];
	FinderItem *item = [items objectAtLocation:url];
	[url release];
	return item;
}

void PluginMain(int32_t selector, PA_PluginParameters params)
{
	try
	{
		int32_t pProcNum = selector;
		sLONG_PTR *pResult = (sLONG_PTR *)params->fResult;
		PackagePtr pParams = (PackagePtr)params->fParameters;

		CommandDispatcher(pProcNum, pResult, pParams); 
	}
	catch(...)
	{

	}
}

void CommandDispatcher (int32_t pProcNum, sLONG_PTR *pResult, PackagePtr pParams)
{
	switch(pProcNum)
	{
			// --- Comment
			
		case 1 :
			Finder_set_comment(pResult, pParams);
			break;
			
		case 2 :
			Finder_get_comment(pResult, pParams);
			break;
			
			// --- Lock
			
		case 3 :
			Finder_set_locked(pResult, pParams);
			break;
			
		case 4 :
			Finder_get_locked(pResult, pParams);
			break;
			
			// --- Extension
			
		case 5 :
			Finder_set_extension_hidden(pResult, pParams);
			break;
			
		case 6 :
			Finder_get_extension_hidden(pResult, pParams);
			break;
			
			// --- Sort
			
		case 7 :
			Finder_SORT_ARRAY(pResult, pParams);
			break;
			
			// --- Information
			
		case 8 :
			Finder_get_display_name(pResult, pParams);
			break;
			
		case 9 :
			Finder_get_description(pResult, pParams);
			break;
			
		case 10 :
			Finder_get_kind(pResult, pParams);
			break;
			
			// --- Control
			
		case 11 :
			Finder_reveal(pResult, pParams);
			break;
			
		case 12 :
			Finder_trash(pResult, pParams);
			break;
			
	}
}


// ------------------------------------ Comment -----------------------------------


void Finder_set_comment(sLONG_PTR *pResult, PackagePtr pParams)
{	
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		NSString *comment = Param2.copyUTF16String();
		item.comment = comment;
		[comment release];
		returnValue.setIntValue(1);
	}
	
	returnValue.setReturn(pResult);
}

void Finder_get_comment(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setUTF16String(item.comment);
		returnValue.setIntValue(1);
	}
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

// ------------------------------------- Lock -------------------------------------


void Finder_set_locked(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		item.locked = Param2.getIntValue();
		returnValue.setIntValue(1);
	}	
		
	returnValue.setReturn(pResult);
}

void Finder_get_locked(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setIntValue(item.locked);
		returnValue.setIntValue(1);
	}	
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

// ----------------------------------- Extension ----------------------------------


void Finder_set_extension_hidden(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		item.extensionHidden = Param2.getIntValue();
		returnValue.setIntValue(1);
	}	
	
	returnValue.setReturn(pResult);
}

void Finder_get_extension_hidden(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setIntValue(item.extensionHidden);
		returnValue.setIntValue(1);
	}	
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

// ------------------------------------- Sort -------------------------------------

int sortWithOption(id string1, id string2, void *context)
{
	static NSStringCompareOptions options = 
	NSCaseInsensitiveSearch | NSNumericSearch |
	NSWidthInsensitiveSearch | NSForcedOrderingSearch;
	
	NSLocale *locale = (NSLocale *)context;
	
    NSRange string1Range = NSMakeRange(0, [string1 length]);
	
    return [string1 compare:string2
                    options:options
					  range:string1Range
					 locale:locale];
}

void Finder_SORT_ARRAY(sLONG_PTR *pResult, PackagePtr pParams)
{
	ARRAY_TEXT Param1;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	uint32_t i, length = Param1.getSize();
	NSMutableArray *stringsArray = [[NSMutableArray alloc]initWithCapacity:length];
	NSString *_string;
	
	for(i = 0; i < length; ++i){
		_string = Param1.copyUTF16StringAtIndex(i);
		[stringsArray insertObject:_string atIndex:i];
		[_string release];
	}
		
	NSArray *sortedArray = [stringsArray sortedArrayUsingFunction:sortWithOption context:[NSLocale currentLocale]];
	
	for(i = 0; i < length; ++i){
		Param1.setUTF16StringAtIndex([sortedArray objectAtIndex:i], i);
	}	
	
	Param1.toParamAtIndex(pParams, 1);
}

// ---------------------------------- Information ---------------------------------


void Finder_get_display_name(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	Param2.fromParamAtIndex(pParams, 2);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setUTF16String(item.displayedName);
		returnValue.setIntValue(1);
	}

	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

void Finder_get_description(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setUTF16String(item.objectDescription);
		returnValue.setIntValue(1);
	}
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

void Finder_get_kind(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_TEXT Param2;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		Param2.setUTF16String(item.kind);
		returnValue.setIntValue(1);
	}
	
	Param2.toParamAtIndex(pParams, 2);
	returnValue.setReturn(pResult);
}

// ------------------------------------ Control -----------------------------------


void Finder_reveal(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		[item reveal];
		returnValue.setIntValue(1);
	}
	
	returnValue.setReturn(pResult);
}

void Finder_trash(sLONG_PTR *pResult, PackagePtr pParams)
{
	C_TEXT Param1;
	C_LONGINT returnValue;
	
	Param1.fromParamAtIndex(pParams, 1);
	
	FinderItem *item = getFinderItem(Param1);
	
	if([item exists]){
		[item delete];
		returnValue.setIntValue(1);		
	}
	
	returnValue.setReturn(pResult);
}

// Copyright, 2023, by NGD Studios AB. All rights reserved.

#pragma once

#include <CoreMinimal.h>
#include <Blueprint/UserWidget.h>

#include "QuickActions.generated.h"

class UWorkrate;
class UTouchlineShouts;
class UCoachEmotes;


/**
 * @see UQuickActionsButton
 * @see WBP_QuickActions
 */
UCLASS()
class FOOTBALL_API UQuickActions : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct() override;
	void NativeDestruct() override;
	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void CheckIfMouseClickIsOutsideGeometry();
	
public:
	//~=================================================================================================================
	// Getters
	//~=================================================================================================================
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetWorkrate)
	UWorkrate* K2_GetWorkrate() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetTouchlineShouts)
	UTouchlineShouts* K2_GetTouchlineShouts() const;

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=GetCoachEmotes)
	UCoachEmotes* K2_GetCoachEmotes() const;

protected:
	//~=================================================================================================================
	// Events
	//~=================================================================================================================

	UFUNCTION(BlueprintImplementableEvent, DisplayName=OnSelectedIndex)
	void K2_OnSelectedIndex(int32 Index);

	/**
	 * Reset the selection status. That means that any visual effect should be stopped and hidden.
	 * It's called by out-side-click and direct.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=OnUnselected)
	void K2_OnUnselected();
	
public:
	//~=================================================================================================================
	// Assistant
	//~=================================================================================================================

	/**
	 * Display a message directly. It's UMG dependent the way of do this.
	 * @param Message The message to display
	 * @param Timeout If greater than zero, how much seconds the message remains until hidden itself
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=DisplayAssistantMessage)
	void K2_DisplayAssistantMessage(const FText& Message, float Timeout);

	/**
	 * Hide a previous message. It's UMG dependent the way of do this.
	 */	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=HideAssistantMessage)
	void K2_HideAssistantMessage();

	/**
     * Display a notify in assistant area. It's UMG dependent the way of do this.
     * @param bVisible True to display, false to hide
     */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=DisplayAssistantNotify)
	void K2_DisplayAssistantNotify(bool bVisible);

	/**
	 * Push a message in the stack of assistant messages. This means that the message don't display
	 * directly like K2_DisplayAssistantMessage, instead awaits until next call K2_DisplayAssistantMessage.
	 * @param Message The message to display
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=PushAssistantMessage)
	void K2_PushAssistantMessage(const FText& Message);

	
public:
	UFUNCTION(BlueprintCallable)
	void SelectIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void SetLockSelectIndex(int32 Index, bool bLocked);
	
	/**
	 * Reset the selection status. That means that any visual effect should be stopped and hidden.
	 */
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, DisplayName=Unselected)
	void K2_Unselected();

	/**
	 * Initialize the widget that limit the zone of this widget. It's used to check out-side-clicks.
	 * @param Widget The widget used to limit the zone
	 */
	UFUNCTION(BlueprintCallable, DisplayName=SetupZoneLimit)
	void K2_SetupZoneLimit(UWidget* Widget);

public:
	//~=================================================================================================================
	// Ellipse formulas
	//~=================================================================================================================
	
	/**
	 * Calculates the position of a vertex on an ellipse based on a set of parameters.
	 * 
	 * @param Angle In radians, represents the angular position of the vertex on the ellipse.
	 * @param Center The center point of the ellipse.
	 * @param MajorAxis The major (longest) axis of the ellipse.
	 * @param MinorAxis The minor (shortest) axis of the ellipse.
	 * @param Rotation The rotation of the ellipse, in radians.
	 * @param Radius Determines the scale of the ellipse.
	 * @return Returns a 2D vector representing the position of the vertex on the ellipse.
	 */
	UFUNCTION(BlueprintPure)
	static FVector2f GetEllipseVertex(float Angle, const FVector2f& Center, float MajorAxis, float MinorAxis, float Rotation, float Radius);

	/**
	 * Calculates the normal vector of an ellipse at a specific point defined by the 'Angle'.
	 *
	 * @param Angle In radians, represents the angular position of the point on the ellipse where the normal needs to be calculated.
	 * @param MajorAxis The major (longest) axis of the ellipse.
	 * @param MinorAxis The minor (shortest) axis of the ellipse.
	 * @param Rotation The rotation of the ellipse, in radians.
	 * @return Returns a 2D vector representing the direction of the normal at the point on the ellipse specified by the 'Angle'.
	 */
	UFUNCTION(BlueprintPure)
	static FVector2f GetEllipseNormal(float Angle, float MajorAxis, float MinorAxis, float Rotation);

	UFUNCTION(BlueprintPure)
	float ProjectMouseCoordToEllipseAngle(const FVector2D& MouseCoord, const FGeometry& Geometry, float Rotation, float MajorAxis, float MinorAxis);
	
private:
	UPROPERTY()
	UWidget* LimitWidget {};

	bool bLockSelectIndex[3] {};
};

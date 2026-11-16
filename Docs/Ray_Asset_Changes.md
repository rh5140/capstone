# Changes to Ray's assets (Summer, Nov 11-16, 2026)

Every change Qitao made to an asset Ray made, so nothing is a surprise. Your nodes were left in place; where we added
logic, it sits next to yours. Old values are listed so any line can be undone by hand. Everything else in this branch
is new (`BP_TA_*`, `BP_Inspect_*`, `BP_NPC_*`, `BP_StoryState`, `BP_DialogueManager`, `BP_Interactable_Door`,
`BP_Interactable_NPC`, the `ST_Summer_*` tables). How the new parts fit together: `Docs/Summer_Dialogue.md`.

## Blueprints (logic)

- `BP_CapstoneCharacter`
  - New function `TA_StepNoiseRange`. The footstep `MakeNoise` range is 120 on grass and 170 on other floors. It was 0
    before, so the monster heard you anywhere.
  - New function `TA_StepSound` with vars `StepSoundFloor`, `StepSoundGrass`, `StepSoundCarpet`: the footstep sound
    changes with the floor material. Floor and carpet use your wood steps; grass uses `TA_GrassSteps_Loop`.
  - The flipbook writes custom depth (stencil 2), used for the outline behind walls.
  - Pause (Nov 16): new function `TA_TogglePause`, new bool `TA_PrevCursor` and an `Esc` key event (Execute When
    Paused). It opens or closes our `WBP_TA_PauseMenu`: pause the game, show the cursor, input Game and UI; on close
    the cursor goes back to what it was and input is Game only. Esc only reaches the pawn while its input is on, so
    dialogue, cutscenes and the ending cannot be paused with Esc.
- `BP_Interactable`
  - EndOverlap only clears the target when `InteractTarget == self`. Before, any overlap ending cleared it.
  - SetActive: when the player is already inside the box, it becomes the target on the next frame.
  - New editable string `NewTaskSub`. After `UpdateTaskText(NewTask)` it fills the HUD's second task line
    (`TaskSubText`, shown as "• text"). When it is empty, the line is cleared.
- `BP_Interactable_ChangeWorld`
  - DoOnce first, because `SucceedInteraction` fired twice and caused 4 pending-kill errors. Order: Night first, then
    the delay (iris time + 0.1), then DisableActors (with an IsValid check), then spawn the toad.
  - Brown-noise `PlaySound2D` volume 1 -> 0.18.
  - The spawned toad gets `SetPatrolPoints(TA_PatrolN1)` and starts at MK_02. The spawned crying trigger moved into
    the bathroom.
- `BP_Interactable_PickUp`: plays the pickup sound `maou_se_onepoint07` first.
- `BP_SoundTimedTrigger`: sound -> `TA_ChildSob_8s`, `AudioInterval` 4 -> 8.
- `BT_SummerToad` / `BTT_PatrolPath`: the patrol point was written to the `EnemyActor` key, but MoveTo reads
  `PatrolLocation`, so the toad stood still. The patrol task now writes `PatrolLocation`.
- `WBP_HUD`
  - The task paper has two lines: `TaskText` (32, the main task) and the new `TaskSubText` (25, brown, "• sub task").
    `UpdateTaskText` clears the second line first.
  - The opening text was "Task: Clean up your room". It is now "Clean up your room." with the second line
    "• Pick up your glowstick and Teddy."
  - The task paper is scaled x1.2 and slid 250 px left (Position X -250), so it ends sooner; the two task lines are
    700 wide (were 820).
  - The `GlowstickR` image (the "R" glowstick icon) is removed. `PopulateInventorySlot` case 0 now only shows
    `Glowstick`; the node that showed `GlowstickR` is gone. `Btn_Glowstick_R` stays in `UI/`.
  - `InspectionTextBox` sits at -245 from the bottom (was -215), so it no longer touches the `[E]` prompt box.
  - `ActionPrompt` / `InspectionText` are 30, cream-coloured, in a dark rounded box. An empty text hides the box.
  - The drawing popup is centred at 1100 x 619 and fades in and out.
  - Pause icon (Nov 16): `Construct` binds `Button_3` OnClicked to a new custom event `TA_PauseClicked`, which calls
    the player's `TA_TogglePause`. Your Construct was empty before.
  - A task sound plays in `UpdateTaskText`: `PMH_Drastic_BowedPlate_01` in N* stages, `maou_se_system17` otherwise.
- `BP_CapstoneHUD`, `BP_Interactable_SceneChange`: iris transition timing. These changes were in the first PR and are
  already in the earlier commits.

## Asset settings

- `BP_SummerToad`: capsule radius 34 -> 28 (half height 88), so it fits between the kitchen props.
- `LS_OpenBedroomDoor`: Rotation.Z key at frame 30, -90 -> +90. The kid's room door now opens into the room
  instead of across the hallway, where it trapped the toad.
- `UI/DrawingA..D`: replaced with Jocelyn's paper drawings. Same asset names, so your HUD references still work.
- `Protagonist/Adult/*` (12 sprites): custom pivot 40 px below the centre, so the taller adult stands on the floor
  in the SafeRoom.
- `Audio/FreeToUse` volumes: `slime-squish-12` 1.0 -> 0.316, `footsteps-on-wood-floor` 1.0 -> 1.603.
- `Config/DefaultEngine.ini`: `r.CustomDepth=3` (outline, first PR). The navmesh settings are `CellSize` 19 -> 10
  and `AgentRadius` 34 -> 30. With those, the toad finds paths around the kitchen island.
- Packaging (Nov 16): `DefaultEngine.ini` `GameDefaultMap` is `L_SafeRoom` (was the template's `Lvl_TopDown`).
  `DefaultGame.ini` has `ProjectName=From the Shadows` and lists the 6 SafeRoom / Summer maps in `MapsToCook`.
  Summer is opened by name, so without the list it is left out of the build.

## Placed actors in `L_Summer*`

- Task texts (`NewTask` + new `NewTaskSub`). The "Task:" prefix is gone, so they match the story tasks.
  - `OpenChildDoor`: "Find Mom in the backyard." / "Follow the party noise outside."
  - `Mom1`: "Record the baby's cry." / "Hold Teddy close to the stroller."
  - `PickUp_DrawingA`: "Show Mom your drawing." / "Find Mom in the backyard."
  - `ChangeWorld`: "Survive the night." / "Stay quiet and keep out of its sight."
- `OpenChildDoor`: prompt "[E] Open". `UnlockList` holds the kid's room inspection points.
- `PickUp2_Bear`: trigger box (140, 130, 100) offset (-40, -25, 0) and `DisableAfterInteracting` on.
- `BP_BasicAudioPlayer` (party sound): tag `TA_DayOnly`, so it fades out at night.
- The `BP_SoundTimedTrigger` by the stroller (tag `EnemyTarget`) was removed.
- `Mom1`, `RecordStroller`, `ChangeWorld`, `PickUp_DrawingA`: trigger collision off and tags added, because our NPCs
  call them.
- All `BP_Interactable*` boxes: `CanEverAffectNavigation` off. The grey placeholder meshes on NPC and door instances
  are empty with no collision. `Cylinder_glow_0/1` have no collision. NPC_3's sprite is hidden, not deleted.
- The kid's desk group, including your glowstick and `Cylinder_glow_0/1`, moved +40 Y.
- The toad patrol uses tagged markers: `TA_PatrolN1` = MK_03..06, `TA_PatrolN2` = MK_08, MK_07 and the new
  `TA_PatrolN2_HallWest`.

## Not checked in the editor

These come from Qitao's script notes:
- which key the `BT_SummerToad` patrol node finally reads;
- the two audio volumes.

Please glance at them when you open the project.

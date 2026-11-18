# Changes to Ray's assets (Summer, Nov 11-16, 2026)

Every change Qitao made to an asset Ray made, so nothing is a surprise. Your nodes were left in place; where we added
logic, it sits next to yours. Old values are listed so any line can be undone by hand. Everything else in this branch
is new (`BP_TA_*`, `BP_Inspect_*`, `BP_NPC_*`, `BP_StoryState`, `BP_DialogueManager`, `BP_Interactable_Door`,
`BP_Interactable_NPC`, the `ST_Summer_*` tables). How the new parts fit together: `Docs/Summer_Dialogue.md`.

## Blueprints (logic)

- `BP_CapstoneCharacter`
  - Nov 18: `UpdateAnimation` (Tick) sets `FacingDirection` from the velocity while moving (left / right wins on
    diagonals: Vy^2 >= 0.81 Vx^2), then your `SetIsMoving` chain as before. Your W / A / S / D Pressed setters
    stay for turning on the spot. With 3+ keys held the last pressed key used to pick the walk, so it could face
    left while moving right (round5/facing_from_velocity.py).
  - New function `TA_StepNoiseRange`. The footstep `MakeNoise` range is 300 on grass and 400 on other floors (Nov 17: the
    toad could not hear the player walking around it; was 120 / 170). It was 0
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
  - Dialogue box (Nov 16): new instance vars `UseDialogueBox`, `DialogueLine` (a key of `ST_Summer_Dialogue`) and
    `DialogueDone`. When `UseDialogueBox` is on, the first `Interact` plays that line in the NPC dialogue box (the
    player is held) and nothing else happens yet. `BP_DialogueManager` calls `Interact` again after the last line, and
    then your chain (click, `SucceedInteraction`) runs as before. With the flag off, nothing changes.
  - More lines (Nov 17): new editable name array `DialogueMore` (and a scratch array `TA_LinesTmp`). The dialogue
    box plays `DialogueLine` and then every key in `DialogueMore`. Empty = one line, as before. Used on the SafeRoom box
    (`BP_Interactable_SceneChange`) for the lines before the jump to Summer.
  - `L_SafeRoom` desk and bed (Nov 17): `UpdatesTask` on, `NewTask` "Another sleepless night.", `NewTaskSub` "Try to get
    some sleep." (desk) / "Look in the box by the bed." (bed). The desk's `UnlockList` (the bed) was set again after a
    reload had cleared it.
  - `L_SafeRoom` `Debris_Papers` moved 110 cm toward the door side (x 62 -> -48), away from the bed, with our papers
    inspection point on it, so the bed is not out-targeted.
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
    590 wide (were 820, then 700; Nov 18: the second line ran past the torn edge, so the sub lines are kept
    under 40 characters too).
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

- `BTT_PatrolPath` (Nov 17): the two debug Print Strings ("Hello", "womp") print to the log only, not the screen.

- `BP_SummerToad` (Nov 18): capsule radius 24 -> 18 (easier to dodge). `BP_SummerToadController`: LineOfSightTimer
  3 -> 5 (the chase lasts 5 s after the last heard step). Your behaviour tree is unchanged.
- `DefaultEngine.ini` (Nov 18): one SupportedAgents entry "Default", radius 24, matching RecastNavMesh AgentRadius.
  Without it the runtime navmesh used the engine default radius 35, which sealed the phone corner and the island aisles.

## Asset settings

- `BP_SummerToadController` (Nov 17): the AIPerception Hearing sense `MaxAge` 0 -> 3 s. With 0 a heard noise never
  expired, so one player footstep meant a chase for the rest of the night. Hearing is the toad's only sense.
- `BP_SummerToadController` (Nov 16): `LineOfSightTimer` 0 -> 3. The controller starts a timer of that length when
  the player leaves its sight, and only that timer sets `HasLineOfSight` false; a 0 s timer never fires, so the toad
  chased forever (through walls) and camped the nearest doorway. Now it gives up 3 s after losing sight. Our
  `BP_TA_ToadWatchdog` also clears the chase keys when the toad stands still while chasing (see Summer_Dialogue.md).
- `BP_SummerToad`: capsule radius 34 -> 28 -> 24 (half height 88), so it fits between the kitchen props (Nov 17: the
  aisles beside the kitchen island are 89 / 91 cm).
- `Mom_Sprite` / `Dad_Sprite` (placed, Day): tags `TA_HorrorMom` / `TA_HorrorDad` and a Movable sprite component, so our
  `BP_TA_Driver` can swap Jocelyn's horror sprites in when a Night switch starts (Day swaps them back).
- `LS_OpenBedroomDoor`: Rotation.Z key at frame 30, -90 -> +90. The kid's room door now opens into the room
  instead of across the hallway, where it trapped the toad.
- `UI/DrawingA..D`: replaced with Jocelyn's paper drawings. Same asset names, so your HUD references still work.
- `Protagonist/Adult/*` (12 sprites): custom pivot 40 px below the centre, so the taller adult stands on the floor
  in the SafeRoom.
- `Audio/FreeToUse` volumes: `slime-squish-12` 1.0 -> 0.316, `footsteps-on-wood-floor` 1.0 -> 1.603.
- `Config/DefaultEngine.ini`: `r.CustomDepth=3` (outline, first PR). The navmesh settings are `CellSize` 19 -> 10
  and `AgentRadius` 34 -> 24 (the RecastNavMesh actor in `L_Summer` too; it had kept 35). With those, the toad finds paths around the kitchen island.
- Packaging (Nov 16): `DefaultEngine.ini` `GameDefaultMap` is `L_SafeRoom` (was the template's `Lvl_TopDown`).
  `DefaultGame.ini` has `ProjectName=From the Shadows` and lists the 6 SafeRoom / Summer maps in `MapsToCook`.
  Summer is opened by name, so without the list it is left out of the build. `IncludeDebugFiles=False` keeps the
  216 MB .pdb out of the build.
- `Capstone.uproject`: `NNEDenoiser` and `NNERuntimeORT` are disabled. The engine turns NNEDenoiser on by default and
  it pulls in DirectML, onnxruntime and its denoiser models; the game does not use them. The build went from 762 MB
  to 409 MB.

## Placed actors in `L_Summer*`
- Nov 18: after the navmesh fix the N2 toad start, `MK_07` patrol tag, the phone lure and the plush point are back by the
  phone (a temporary move to (-700, -960) on Nov 17 is undone). `RecastNavMesh-Default` agent radius 24.

- `NPC_1_Sprite` (your lawn guest) moved to MK_02 (462, -1185), away from Mom (Nov 17); our `NPC_GuestLawn` stands on it and talks (Jiayi's A03 / A04 /
  A07). A second guest `NPC_GuestFood` (NPC_2 sprite) is new, south of the long party table.
- Task texts (`NewTask` + new `NewTaskSub`). The "Task:" prefix is gone, so they match the story tasks.
  - `OpenChildDoor`: "Find Mom in the backyard." / "Follow the party noise outside."
  - `Mom1`: "Record the baby's cry." / "Hold Teddy close to the stroller."
  - `PickUp_DrawingA`: "Show Mom your drawing." / "Find Mom in the backyard."
  - `ChangeWorld`: "Survive the night." / "Stay quiet and keep out of its sight."
- SafeRoom texts (Nov 16): the desk, bed and plush-box lines now use Jiayi's environment doc (SR01, SR03, SR02:
  "The computer is still on...", "I'm so tired...", "My old teddy bear is at the bottom..."). Your earlier texts were
  "...It's such a mess. Where do I even start?", "...At least the bed is made.", "My old plush. The patch on its back
  is still there."
- Dialogue box instead of the bottom text (Nov 16; their `InspectionText` is empty now, the text is the line):
  `PickUp_Glowstick` (X_GLOW01), `PickUp2_Bear` (X_TEDDY01), `OpenChildDoor` (X_KIDDOOR01); in `L_SafeRoom`
  `BP_Interactable_Desk` (X_SR_DESK01), `BP_Interactable_Bed` (X_SR_BED01), `BP_Interactable_SceneChange`
  (X_SR_PLUSH01; the level changes after the line). `ChangeWorld` lost its text; its line X_CW01 now ends Mom's M06
  dialogue. `L_SafeRoom` has a `BP_DialogueManager` now (`TA_SR_DialogueManager`).
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

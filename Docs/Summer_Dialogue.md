# Summer dialogue and doors

Blueprints only. Each new Blueprint has a Description (hover it in the Content Browser).

## Where things are

- `Blueprints/Dialogue/BP_StoryState`: stage, flags and task text. One `Story_State` in `L_Summer`.
- `Blueprints/Dialogue/BP_DialogueManager`: shows the lines, one per E press.
- `Blueprints/Interactable/BP_Interactable_NPC`: child of `BP_Interactable`, base for anyone who talks.
  The NPCs in `Interactable/NPC/` only override `GetDialogue` (first matching rule wins).
  Per placed NPC: `VisibleStages` (empty = always there; otherwise it and its attached sprite only exist in those
  stages, e.g. Dad in D4) and `RingSound` / `RingStages` (the phone rings in D4_Phone).
- `Blueprints/Interactable/BP_Interactable_Door`: child of `BP_Interactable`. Locked doors show their
  `InspectionText`; unlocked ones open the `BP_TA_SlidingDoor` with the tag in `OpenTag`.
- `Blueprints/Interactable/BP_Interactable_Inspect`: child of `BP_Interactable`, an environment inspection point.
  Set `FixedKey` (and optionally `FirstKey` / `NightKey`) to keys of `ST_Summer_Inspect`; the text shows in the HUD
  inspection box. The kid's room points and the desk switch on when the kid's room door opens.
- `Environment/TA/BP_TA_InteractPicker`: one in `L_Summer`. Where triggers overlap, it makes the nearest active one
  the target.
- `Blueprints/Dialogue/BP_Trigger_Stage`: walk-in trigger. While the stage is in `Stages`, it calls `Target`'s
  interaction (e.g. entering the kitchen in N2).
- `Data/Dialogue/`: all text (lines, speaker names, task text, inspection text) in four String Tables.
- `Environment/TA/BP_TA_Camera`: during dialogue it moves to the midpoint of the player and the speaker and narrows
  the FOV (`FocusFOVScale`).
- `Environment/TA/BP_TA_StepRings`: night footstep rings around the player (`L_Summer_Night`). The monster hears
  footsteps 120 cm on grass, 170 cm on floors (`TA_StepNoiseRange` in `BP_CapstoneCharacter`); the rings are drawn
  smaller (70 / 100). Boards and the broken floor show a deep red ring (`MI_TA_StepRing_Loud`, 300 cm), the cans a
  brighter red one (`MI_TA_StepRing_Can`, 450 cm). The cans also have a steady moonlight rim near the player
  (Custom Depth stencil 4 in `PP_TA_Highlight`). While a bear-point lure rings (`BP_TA_Lure` Busy) a creak board or
  can still sounds but does not pull the toad away (`TA_AnyLureBusy` in `BP_TA_CreakBoard`).
- `Environment/TA/PP_TA_Highlight`: also draws the player as an outline behind walls (custom depth stencil 2;
  `r.CustomDepth=3` in `DefaultEngine.ini`).
- N1 cue in `L_Summer_Night`: kitchen light, rings at the glass door and a phone ring (`Audio/FreeToUse`).
- Sounds from SkycideJeno (`Audio/FreeToUse`, Nov 15): baby laugh on the stroller and Mom, crying at the N2 bathroom
  and in the ending, an item sound on the key, a task sound when a Day objective appears (`BP_StoryState.SetStage`).
- Jocelyn's cutouts (`NPCs/`, Nov 12-14): `Dad_Normal_Sprite` on Dad; `Baby_Sprite`, `Mom_Horror_Sprite`,
  `Dad_Horror_Small_Sprite` are imported but not placed yet.
- `Blueprints/Dialogue/BP_TA_CreakBoard`: loose boards on the N1 yard route. Stepping on one creaks and calls
  `MakeNoise`, so the toad hears it (its AI is unchanged). The first creak sets N1_Board. Also used for the N1 cans
  around the long yard tables (`Can_1` ... `Can_8`, louder, MakeNoise 1300 cm; floraphonic's Kick The Can 1 / 2 from
  Pixabay, sources in the team's SFX doc) and for
  the N2 broken floor in the house (`BrokenFloor_049` kitchen and `_051` living room, `wood-floor-broken` on the old greybox Creaky
  markers, N2 .. N2_Bath).
- `Blueprints/Dialogue/BP_TA_CreaturePuppet`: the scripted creature in N2. The player starts inside the kitchen (the
  back door only leads in); the creature comes in and becomes `BP_SummerToad`, patrolling `TA_PatrolN2`.
- `Blueprints/Dialogue/BP_TA_Lure` + `BP_Inspect_PlaceBear`: two fixed bear points in N2 (by the phone, in the hall).
  Placing the plush there plays the recorded phone ring and calls every toad to that point for a while.
- `Blueprints/Dialogue/BP_TA_Checkpoint`: one in `L_Summer`. If a toad gets within `CatchRadius` at night, the screen
  irises out and the player goes back to `N1Player` / `N2Player`, the toads to `N1Toad` / `N2Toad`. N1 restarts
  (stage N1). N2 keeps its stage, the key and the unlocked door; only the plush flag is cleared, so it can be set
  down again.
- `Blueprints/Dialogue/BP_TA_DadCutscene`: D4 (the 1019 meeting doc's CS04): the phone rings, Dad comes in from the deck
  through the glass door and walks to the phone (player frozen), talks, then waits beside the glass door. The player walks
  up and talks to him ("wait"), he goes out and shuts the door, D4_Phone. Routes are `PathIn` / `PathOut` / `PathExit`
  on the placed `TA_DadCutscene`; it finds Dad and the door by tag (`TA_CutDad`, `TA_CutDoor`) because Dad lives in
  `L_Summer_Day`. The phone ring fades out when Dad reaches the phone. The player is free again once Dad has walked
  past the kid (`PathIn` index 3), not only when he reaches the phone, and the glass door shuts then. `TA_GlassWall`
  (an invisible wall, switched by `BP_TA_StageBlocker` `TA_GlassWallSwitch`) keeps the player inside in D4 .. D4_Recorded. `PathExit` ends just outside the glass door,
  where Dad shows again in D4_Recorded (`NPC_Dad` VisibleStages D4 + D4_Recorded).
- `Blueprints/Dialogue/BP_TA_SwingDoor`: hinged door leaf that swings open in `OpenStages` (the N2 bathroom door).
  `TA_BathRoof` on `BathRoof_Holder` covers the bathroom in N2 until the door opens.
- `Interactable/NPC/BP_Inspect_DrawingA` ... `D`: Jiayi's crayon drawings (section 6) at the greybox Clue markers.
  One caption line, then the page fades in. Pictures are `UI/DrawingA` ... `D` (Jocelyn's paper versions).
  `HideFlag drawing_<x>_seen` (a `BP_Interactable_NPC` variable): once the drawing is in the HUD column it is gone
  from the world. Drawing B is on the yard's small round table, D0 .. D4_Recorded and N1.
- `BP_CapstoneCharacter`: `StepSoundFloor` / `StepSoundGrass` / `StepSoundCarpet` pick the footstep clip from the
  material under the feet (`TA_StepSound`). Grass = `TA_GrassSteps_Loop` (SkycideJeno's three grass steps in a loop);
  floor and carpet are the wood clip.
- `Blueprints/Dialogue/BP_TA_HopToad`: the small Day toad hopping along the sunflower bed (`L_Summer_Day`).
- `Blueprints/Dialogue/BP_TA_StageHighlight`: outlines a mesh in some stages (the desk drawing toy in D1, the
  bathroom door leaf in N2_Inside / N2_Key, the N2 scissors before the key).
- `Blueprints/Dialogue/BP_TA_Flicker`: the glitching dark red N1 kitchen light.
- `Blueprints/Dialogue/BP_TA_RandomSound`: random sounds at random gaps, optionally following the toad, only while it
  moves / stands, or only near the player. Placed in folder `Audio/SfxDoc`: baby laughs, cicadas, kids chatter (Day);
  wind, the toad's walk / slime / frog / idle, heartbeat and tension (Night). Uses follow Jiayi's SFX doc.
  Sounds are attached to the actor (it moves onto the toad when `FollowToad`), fade in over `FadeIn`, and
  `TA_Silence` fades them out. `SFX_DayBGM` (`Audio/Round4`) plays Greer's Safe Room music in Day and END.
- `BP_TA_Driver`: `Day()` / `Night()` / `Real()` first call `TA_SilenceWorld` (every `BP_TA_RandomSound` and every
  toad's sounds fade out as the switch starts, not 1.7 s later at the level swap) and `TA_DayOnlyFade` (actors tagged
  `TA_DayOnly`, i.e. Ray's party-chatter `BP_BasicAudioPlayer`, fade out at night and back in by day).
  `Swap_Night` starts the night brown noise (`ChangeWorld.NightLoop`) when ChangeWorld did not (N2).
- N1 phone cue: `N1Cue_PhoneRinger` (`BP_Inspect_PlayRing`, never shown) rings in N1 / N1_Board only; the old looping
  `N1Cue_PhoneRing` AmbientSound no longer auto-activates.
- `TA_Curtain_Second` (`L_Summer_Night`): the second shower-curtain half, so both are drawn in N2_Bath and only one is
  left in Day / END.
- The full list of sounds (where, when, how long, 2D / 3D, when they stop) is in the team's audio table
  (`夏季关卡_音源对照表_1116`).
- `Protagonist/BathtubSobbing/PFB_BathtubSobbing` (the team's 9 sobbing frames) on
  `Child_Sob`, the child in the bathtub in END (attached to `NPC_Child`; the old NPC_3 placeholder is hidden).
- `Blueprints/Dialogue/BP_TA_ToadGlow`: marks every toad's mesh for `PP_TA_Highlight` (Custom Depth, stencil 3), which
  draws a red rim around it at any distance, pulsing slowly (2.4 s), so the black toad reads at night.
- N2 toad: patrol `TA_PatrolN2` = MK_07 (living room), MK_08 (kitchen), `TA_PatrolN2_HallWest` (hallway west end;
  MK_09 at the bathroom / kid's room doors is no longer a patrol point). `BP_TA_ToadWatchdog` (persistent level): if the
  toad stands still over `Threshold` (4 s) while no lure rings, it moves on to its next patrol point and its behaviour
  tree restarts. Navmesh agent radius 30 (was 34 / 35) and cell size 10 (was 19; 19 cm cells rounded the radius up to
  ~40 cm and erased the aisles beside the kitchen island) for the narrow doorways; the toad's capsule radius is 28.
  The kitchen island is 0.8x as wide and its greybox `Prop_089` has no collision, so both aisles have navmesh.
- Kid's room door: Ray's `LS_OpenBedroomDoor` (D1 intro) now swings the leaf +90 (into the room) instead of -90
  (into the hallway, where it blocked the toad's patrol).
- N2 scissors: Sirkitree's low-poly scissors (Poly Pizza, CC BY; `Props/Summer/ChildRoom/Scissors`) on the kid's desk.
- `WBP_TA_EndCard` times its fade-ins from game time (`StartTime`), and `BP_TA_Ending` waits 7.5 s before
  `OpenLevel(L_SafeRoom)`, so "END..." always finishes.
- SafeRoom: the adult protagonist's sprites (`Protagonist/Adult`) have a custom pivot 40 px below the centre so the
  taller adult frames stand on the floor (the capsule is the child's).
- Task paper (`WBP_HUD`): `TaskText` shows the main task; the new `TaskSubText` under it (Schoolbell 25 under the 32 main line, the dialogue
  brown 0.45/0.18/0.12) shows "• " + the sub line. `BP_StoryState.UpdateObjective` fills both; the HUD's
  `UpdateTaskText` clears the sub line first (round5/task_two_lines.py). Ray's task updates (`BP_Interactable.NewTask`)
  take a second line from the new `NewTaskSub` (round5/task_sub_ray.py); the opening task, the kid's-room door, Mom1,
  Drawing A and ChangeWorld have one, no "Task:" prefix.
- Depth of field: every world's post-process volume uses f/1.4 (SafeRoom_Real was 1.0; f/2.0 was tried and had too
  little blur; higher = sharper).
- Pause: Esc or the HUD pause icon -> `BP_CapstoneCharacter.TA_TogglePause` adds / removes `WBP_TA_PauseMenu`
  (BackgroundBlur + dim, Resume / Quit, a Controls list on the right; round5/build_pause.py). The SafeRoom intro
  hint (`TA_SR_Hint_Intro`) ends with "Press Esc to pause." In PIE, Esc stops the session; test with the icon.
- N2 bathroom: `Trigger_Bathroom` no longer plays E01 on entering (Stages []); one E on the shower curtain plays E01 +
  X_CURTAIN01 in one dialogue (one camera push-in) and switches to END (round5/bath_one_e.py).
- `Blueprints/Dialogue/BP_TA_Ending`: Switch 4 at the shower curtain (Day, task paper hidden, party sound) and the
  final fade to black (`WBP_TA_EndBlack`) after "Sit beside them".

## Story after Night 1

D4: Dad's cutscene (comes home, talks, goes back out), then the phone rings and is recorded (`Inspect_Phone`). D4_Recorded: Dad
waits outside the glass door; E at the door talks to him through it (F_DOOR01 / F_DOOR02, flag dad_door_talked),
then `TA_DadCutscene` (Steps 7-10) freezes the player, walks Dad away across the yard (`PathLeave`), interacts
`Door_Glass_Kitchen_Back` (tag `TA_BackDoor`, the Night switch) and gives the player back control in N2. N2: start in the kitchen, follow the crying to the locked
bathroom, empty key hook, the key in the plush seam; put the plush on a bear point to lure the creature away, unlock
(N2_Bath). Shower curtain (one E: E01 + X_CURTAIN01): Switch 4, END. Sit beside the
child, fade out. All placed actors of a step share a tag (`TA_M1` ... `TA_M5`).

## Common edits

- Change a line: edit `ST_Summer_Dialogue` (names in `ST_Summer_Speaker`).
- New NPC: duplicate `BP_NPC_ChildA`, edit its `GetDialogue`, add the line keys to both tables, place it in
  `L_Summer_Day` with `IsActive` on.
- New door: place `BP_Interactable_Door`, `IsActive` on, then either tick `Locked` and write `InspectionText`, or
  set `OpenTag` to the sliding door's tag. Doors can also switch to Night (`SwitchToNight`, `MovePlayer` /
  `PlayerTo`, `DestroyTag`) and use `VisibleStages`. A door that switches worlds must sit in `L_Summer`: the
  sublevel it leaves is unloaded and would cut its delayed steps.

Line, stage and flag names are typed text. A wrong line key shows `<MISSING STRING TABLE ENTRY>`.

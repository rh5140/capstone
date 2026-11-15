# Summer dialogue and doors

Blueprints only. Each new Blueprint has a Description (hover it in the Content Browser).

## Where things are

- `Blueprints/Dialogue/BP_StoryState`: stage, flags and task text. One `Story_State` in `L_Summer`.
- `Blueprints/Dialogue/BP_DialogueManager`: shows the lines, one per E press.
- `Blueprints/Interactable/BP_Interactable_NPC`: child of `BP_Interactable`, base for anyone who talks.
  The NPCs in `Interactable/NPC/` only override `GetDialogue` (first matching rule wins).
- `Blueprints/Interactable/BP_Interactable_Door`: child of `BP_Interactable`. Locked doors show their
  `InspectionText`; unlocked ones open the `BP_TA_SlidingDoor` with the tag in `OpenTag`.
- `Blueprints/Interactable/BP_Interactable_Inspect`: child of `BP_Interactable`, an environment inspection point.
  Set `FixedKey` (and optionally `FirstKey` / `NightKey`) to keys of `ST_Summer_Inspect`; the text shows in the HUD
  inspection box. The kid's room points and the desk switch on when the kid's room door opens.
- `Environment/TA/BP_TA_InteractPicker`: one in `L_Summer`. Where triggers overlap, it makes the nearest active one
  the target.
- `Data/Dialogue/`: all text (lines, speaker names, task text, inspection text) in four String Tables.
- `Environment/TA/BP_TA_Camera`: during dialogue it moves to the midpoint of the player and the speaker and narrows
  the FOV (`FocusFOVScale`).
- `Environment/TA/BP_TA_StepRings`: night footstep rings around the player (`L_Summer_Night`). Ring size matches
  the footstep noise the monster hears: 120 on grass, 250 on floors (`TA_StepNoiseRange` in `BP_CapstoneCharacter`).
- `Environment/TA/PP_TA_Silhouette`: shows the player as an outline behind walls (custom depth stencil 2;
  `r.CustomDepth=3` in `DefaultEngine.ini`).
- N1 cue in `L_Summer_Night`: kitchen light, rings at the glass door and a phone ring (`Audio/FreeToUse`).

## Common edits

- Change a line: edit `ST_Summer_Dialogue` (names in `ST_Summer_Speaker`).
- New NPC: duplicate `BP_NPC_ChildA`, edit its `GetDialogue`, add the line keys to both tables, place it in
  `L_Summer_Day` with `IsActive` on.
- New door: place `BP_Interactable_Door`, `IsActive` on, then either tick `Locked` and write `InspectionText`, or
  set `OpenTag` to the sliding door's tag.

Line, stage and flag names are typed text. A wrong line key shows `<MISSING STRING TABLE ENTRY>`.

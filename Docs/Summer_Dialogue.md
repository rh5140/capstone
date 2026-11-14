# Summer dialogue and doors

Blueprints only. Each new Blueprint has a Description (hover it in the Content Browser).

## Where things are

- `Blueprints/Dialogue/BP_StoryState`: stage, flags and task text. One `Story_State` in `L_Summer`.
- `Blueprints/Dialogue/BP_DialogueManager`: shows the lines, one per E press.
- `Blueprints/Interactable/BP_Interactable_NPC`: child of `BP_Interactable`, base for anyone who talks.
  The NPCs in `Interactable/NPC/` only override `GetDialogue` (first matching rule wins).
- `Blueprints/Interactable/BP_Interactable_Door`: child of `BP_Interactable`. Locked doors show their
  `InspectionText`; unlocked ones open the `BP_TA_SlidingDoor` with the tag in `OpenTag`.
- `Data/Dialogue/`: all text (lines, speaker names, task text) in three String Tables.

## Common edits

- Change a line: edit `ST_Summer_Dialogue` (names in `ST_Summer_Speaker`).
- New NPC: duplicate `BP_NPC_ChildA`, edit its `GetDialogue`, add the line keys to both tables, place it in
  `L_Summer_Day` with `IsActive` on.
- New door: place `BP_Interactable_Door`, `IsActive` on, then either tick `Locked` and write `InspectionText`, or
  set `OpenTag` to the sliding door's tag.

Line, stage and flag names are typed text. A wrong line key shows `<MISSING STRING TABLE ENTRY>`.

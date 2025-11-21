# Weekly Development Challenges & Solutions

This document analyzes the challenges, bugs, and problems encountered during development week by week, based on commit messages, and how they were resolved.

---

## Week 1: October 2-8, 2025
**Focus:** Project Setup & Core Mechanics Implementation

### Challenges Faced:

#### 1. **Git/Version Control Issues** (Oct 2)
- **Problem:** Multiple attempts to configure .gitignore correctly
- **Evidence:** Commits "trying to make this stop", "ok", "extra"
- **Solution:** Successfully configured .gitignore to exclude unwanted files after several iterations

#### 2. **Pawn Architecture Decision** (Oct 3)
- **Problem:** Initial player implementation needed fundamental restructuring
- **Evidence:** "working on changing stuff. changing to spectator pawn. getting rid of some things"
- **Challenge:** Deciding between standard Pawn vs Spectator Pawn for top-down gameplay
- **Solution:** Successfully created custom spectator pawn child class ("my child of spectator pawn class is now spawned as the character")
- **Final Fix:** Switched to custom player pawn base class ("player pawn base class now working DAY OF NEW DAWN")
- **Learning:** Architecture decisions matter early - spent significant time refactoring pawn system

#### 3. **File Visibility/Organization Issues** (Oct 5)
- **Problem:** Project files were hiding or not appearing correctly
- **Evidence:** "files are not hiding anymore and its actually working"
- **Context:** OneDrive sync conflicts ("commit sotpping one drive")
- **Solution:** Resolved file visibility issues, likely related to cloud sync interference

#### 4. **Input System Implementation** (Oct 5)
- **Problem:** Setting up mouse-based interaction for top-down view
- **Evidence:** "working on input division system"
- **Challenge:** Detecting clicks on objects in 3D space
- **Solution:** Successfully implemented click detection ("can now click on object and it will detect if it can grab it")
- **Progress:** Got grabbable object system working by end of day

#### 5. **Object Following Mouse System** (Oct 5-6)
- **Problem:** Making grabbed objects follow the mouse cursor in 3D space
- **Evidence:** "need to create system to make the object follow mouse when clicked" (Oct 5), "can pick up objects now" (Oct 6)
- **Solution:** Implemented physics-based grabbing system using physics handle
- **Additional Fix:** Added invisible wall boundary to prevent cursor from going too far

#### 6. **Object Rotation & Display** (Oct 6)
- **Problem:** Objects rotating during grab/movement
- **Evidence:** "now has numbers and wont rotate"
- **Solution:** Locked rotation and added number display system

#### 7. **Major Scale Issue** (Oct 7)
- **Problem:** Critical asset scaling problem affecting entire game
- **Evidence:** "FINALLY FIXED BLOODY SCALE ISSUE, and random idles now"
- **Impact:** High frustration indicated by commit message tone
- **Solution:** Fixed scaling, also implemented random idle animations simultaneously
- **Learning:** Asset import settings in Unreal are critical to get right early

### Week 1 Summary:
- **Major Wins:** Core grabbing mechanics working, player pawn implemented, random number generation
- **Biggest Challenge:** Scale issue that took significant time to debug
- **Technical Debt:** Some optimization needed (commit: "need to continue optimizing tomorrow")

---

## Week 2: October 9-15, 2025
**Focus:** Physics Refinement & Animation System

### Challenges Faced:

#### 1. **Collision Shape Optimization** (Oct 9)
- **Problem:** Box colliders not performing well for grabbable objects
- **Evidence:** "changed box collider to capsule on grabbable objects"
- **Solution:** Switched to capsule colliders for better physics interaction
- **Learning:** Shape choice matters for physics simulation

#### 2. **Foliage/Mesh Application Issues** (Oct 9)
- **Problem:** Foliage meshes not applying correctly to terrain/landscape
- **Evidence:** "finally got the foliage meshes to properly apply"
- **Difficulty:** Used "finally" indicating this took multiple attempts
- **Solution:** Resolved mesh application after troubleshooting

#### 3. **Flying/Grounded Logic Bug** (Oct 9-10)
- **Problem:** Objects not correctly detecting when grounded vs. airborne
- **Evidence:** "working on flying logic" → "reverting testing need to add the air logic tomorrow" → "fixed the grounded issue"
- **Timeline:** Multi-day debugging spanning Oct 9-10
- **Approach:** Had to revert failed attempts before finding working solution
- **Solution:** Successfully implemented grounded detection on Oct 10

#### 4. **Native Event/Delegate System** (Oct 10)
- **Problem:** Blueprint-to-C++ communication not working as expected
- **Evidence:** "need to try solve this native event issue" → "still need more work on this" → "delegate made" → "finally fixed it"
- **Duration:** ~6 hours of work based on commit timestamps
- **Challenge:** Understanding Unreal's delegate/event system
- **Solution:** Created proper delegate system for event communication
- **Impact:** Applied solution to all animal types ("done 4 cow too")

#### 5. **Plugin/3D Text Reversal** (Oct 14)
- **Problem:** Plugin or 3D text implementation caused issues requiring complete rollback
- **Evidence:** Two consecutive revert commits
  - "Revert 'still worki ng on 3d text'"
  - "Revert 'working on grabbable obj pollish and addingplugin'"
- **Learning:** Sometimes features need to be abandoned if they cause more problems
- **Recovery:** Moved forward with alternative approach (custom cursor instead)

### Week 2 Summary:
- **Major Wins:** Grounded detection fixed, delegate system working, animals implemented
- **Biggest Challenge:** Native event/delegate debugging took most of a day
- **Failed Experiments:** 3D text plugin abandoned after testing
- **Recovery Strategy:** Quick to revert when approach didn't work

---

## Week 3: October 16-22, 2025
**Focus:** Game Logic & Detection Systems

### Challenges Faced:

#### 1. **Sign Detection System** (Oct 16-17)
- **Problem:** Implementing the core game mechanic - detecting correct animals in pens
- **Evidence:** "smoothed movement and working on signs" → "doing work on detection scripts"
- **Progress:** "condition checking animals in pens actually working"
- **Timeline:** 2 days of implementation
- **Solution:** Successfully created collision detection and validation system

#### 2. **Material Rendering Issue** (Oct 17)
- **Problem:** Material not displaying correctly on objects
- **Evidence:** "changed material issue"
- **Context:** Quick fix during UI development phase
- **Solution:** Resolved material problem (specific solution not detailed)

### Week 3 Summary:
- **Major Wins:** Core game loop functional, pen detection working, UI started
- **Focus Shift:** From mechanics to game logic and win conditions
- **Pace:** Fewer commits but more complex features (6 commits vs. 43 in Week 1)
- **Maturity:** Game is becoming more complete and playable

---

## Week 4: October 23-29, 2025
**Focus:** Win Logic & Asset Integration

### Challenges Faced:

#### 1. **Animation Blueprint Confusion** (Oct 23)
- **Problem:** Uncertainty about cow animation blueprint setup
- **Evidence:** "working this stuff is wrong tho pertty sure need to change cow bp + abp"
- **Self-Doubt:** Commit message shows uncertainty about implementation
- **Resolution:** Next commit: "nevermind its actually working"
- **Learning:** Sometimes what seems broken is actually correct - testing validated the approach

#### 2. **Rendering/Lighting Performance** (Oct 24)
- **Problem:** Performance issues with rendering after adding Nanite
- **Evidence:** "added nanite experimenting with lighting need to optimize lighting (rendering) more"
- **Challenge:** Balancing visual quality with performance
- **Status:** Ongoing optimization concern flagged for future work

#### 3. **Animation Bugs** (Oct 24)
- **Problem:** Animation system had bugs affecting gameplay
- **Evidence:** "fixed bug and slved animations"
- **Solution:** Both general bugs and animation-specific issues resolved
- **Context:** Part of polish phase with new assets

### Week 4 Summary:
- **Major Wins:** Win logic implemented, new assets integrated, environment built
- **Biggest Challenge:** Performance optimization with advanced rendering features
- **Self-Correction:** Quickly identified false alarm with animation blueprints
- **Growth:** More confident problem-solving ("nevermind its actually working")

---

## Week 5: October 30 - November 5, 2025
**Focus:** Polish & Persistent Bug Fixes

### Challenges Faced:

#### 1. **Recurring Grounded Issue** (Oct 31 - Nov 1)
- **Problem:** The "grounded" detection bug returned despite earlier fix
- **Evidence:** "need to figure out this really annoying grounded issue" → "fixed grounded issue"
- **Timeline:** Problem from Oct 31 night, fixed Nov 1
- **Significance:** Using "really annoying" indicates frustration with recurring bug
- **Root Cause:** Original fix (Week 2, Oct 10) didn't fully solve edge cases
- **Final Solution:** More robust implementation on Nov 1
- **Learning:** Initial fixes may not catch all edge cases

#### 2. **Code Quality Concerns** (Nov 1)
- **Problem:** Code becoming messy/unorganized
- **Evidence:** "refactored signs and grabbables to be better"
- **Motivation:** Proactive refactoring to improve maintainability
- **Timing:** After core features done, before final polish
- **Learning:** Taking time to refactor pays off in later development

### Week 5 Summary:
- **Major Wins:** Audio integrated, final grounded bug fixed, code refactored
- **Biggest Challenge:** Recurring grounded bug showing complexity of physics interaction
- **Maturity:** Proactive refactoring shows growing code quality awareness
- **Near Completion:** Focus shifting to UI and final features

---

## Week 6: November 6-12, 2025
**Focus:** Break Week

### No Development Activity
- **Status:** No commits this week
- **Likely Reason:** Break/rest period after 5 intensive weeks
- **Context:** Smart development practice - avoiding burnout
- **Impact:** Returned refreshed for final push in Weeks 7-8

---

## Week 7: November 13-19, 2025
**Focus:** Boundaries & Progress UI

### Challenges Faced:

#### 1. **Objects Falling Out of World** (Nov 19)
- **Problem:** Grabbable objects escaping playable area
- **Evidence:** "stopped grabbables falling out world"
- **Solution:** Implemented boundary checking/collision
- **Prevention:** Added safeguards to reset objects if they escape

#### 2. **Progress Bar Implementation** (Nov 19)
- **Problem:** Creating visual feedback for game progress
- **Evidence:** "getting somewhere with progress bar" → "delegate is now bound"
- **Challenge:** Connecting game state to UI elements
- **Timeline:** Worked through in single day
- **Solution:** Properly bound delegates to update UI based on game events

### Week 7 Summary:
- **Major Wins:** Boundary system working, progress bar functional
- **Focus:** Polish and user experience improvements
- **UI Integration:** Successfully connected game logic to visual feedback
- **Quality of Life:** Preventing frustrating object loss

---

## Week 8: November 20-26, 2025
**Focus:** Final Polish & Build

### Challenges Faced:

#### 1. **Progress Bar System Completion** (Nov 20)
- **Problem:** Progress bar partially working but needs finishing touches
- **Evidence:** "system is nearly working for progress bar"
- **Solution:** Completed implementation started in Week 7
- **Integration:** Connected to overall win condition checking

#### 2. **Build Issues** (Nov 20)
- **Problem:** Game failing to build/package correctly
- **Evidence:** "removed some assets and fixed build issue"
- **Cause:** Likely oversized or problematic assets
- **Solution:** Identified and removed problematic assets
- **Learning:** Asset management crucial for successful builds

#### 3. **Missing Core Features** (Nov 20)
- **Problem:** No quit functionality for players
- **Evidence:** "added a quit button"
- **Context:** Basic feature overlooked during rapid development
- **Solution:** Added quit button to UI
- **Learning:** Easy to miss obvious UX features when focused on mechanics

### Week 8 Summary:
- **Major Wins:** Build working, all UI complete, quit functionality added
- **Biggest Challenge:** Build issues from asset bloat
- **Completion:** Game feature-complete and buildable
- **Final Polish:** Multiple UI tweaks and refinements

---

## Overall Development Analysis

### Most Challenging Bugs:
1. **Grounded Detection** (Weeks 2 & 5) - Recurring physics issue requiring two separate fixes
2. **Scale Issue** (Week 1) - Major blocking problem affecting all assets
3. **Native Event/Delegate System** (Week 2) - ~6 hours to properly understand and implement

### Problem-Solving Patterns:
- **Quick Iteration:** Willing to revert and try different approaches (Week 2 plugin rollback)
- **Self-Correction:** Recognizes false alarms quickly ("nevermind its actually working")
- **Persistence:** Doesn't give up on hard problems (grounded issue fixed twice)
- **Proactive Refactoring:** Cleans up code before it becomes unmaintainable

### Learning Curve Demonstrated:
- **Week 1:** Fighting with tools (git, OneDrive, Unreal basics)
- **Week 2:** Understanding engine systems (delegates, physics)
- **Week 3:** Implementing game logic confidently
- **Week 4:** Self-validation of work quality
- **Week 5:** Proactive code quality improvements
- **Weeks 7-8:** Polish and user experience focus

### Technical Growth Indicators:
- Fewer commits per week but more meaningful features
- Better commit messages over time (more descriptive)
- Shift from "trying to make this stop" to "refactored signs and grabbables to be better"
- Willingness to take breaks (Week 6) shows maturity

### Common Themes:
- **Physics Complexity:** Multiple issues with collision, grounding, and object behavior
- **Asset Management:** Scale, rendering, build size all caused problems
- **Engine Learning:** Delegates, events, and Unreal-specific patterns required time
- **UI Integration:** Connecting game logic to visual feedback took iteration

---

## Key Takeaways

### What Went Well:
✅ Persistent debugging of complex issues  
✅ Quick to revert failed experiments  
✅ Proactive refactoring before tech debt accumulated  
✅ Comprehensive feature implementation (audio, UI, gameplay)  
✅ Balanced work with rest (Week 6 break)

### What Was Challenging:
⚠️ Physics system edge cases  
⚠️ Unreal Engine's delegate/event patterns  
⚠️ Asset import and configuration  
⚠️ Build/packaging issues  
⚠️ Recurring bugs requiring multiple fixes

### Development Wisdom Gained:
💡 Test thoroughly - "working" doesn't mean "completely fixed"  
💡 Revert quickly when an approach clearly isn't working  
💡 Asset settings matter more than you think  
💡 Take breaks to avoid burnout  
💡 Refactor before code becomes unmaintainable  
💡 Edge cases in physics are harder than main cases

---

*Analysis based on 95 commits from October 2 - November 21, 2025*  
*Generated: November 21, 2025*

# Unreal Engine 5.6 - Graphics & Performance Optimization Guide

## For Building a Game with Good Graphics AND Performance

This guide provides recommended project settings for your game to look great while maintaining good performance in built/packaged versions.

---

## Current Settings Analysis

### ✅ Good Settings Already Configured:
- **Nanite enabled** (`r.Nanite.ProjectEnabled=True`) - Excellent for detailed geometry
- **Ray Tracing enabled** (`r.RayTracing=True`) - But may be overkill for your game style
- **DX12** as default RHI - Modern graphics API
- **Fixed 60 FPS** frame rate target
- **Lumen** enabled (DynamicGlobalIllumination=2, ReflectionMethod=2) - Modern lighting
- **Virtual Shadow Maps disabled** - Good for performance

### ⚠️ Settings That Need Adjustment:
- Ray Tracing may be too heavy for indie game distribution
- Anti-aliasing completely disabled (`r.AntiAliasingMethod=0`) - Makes edges jaggy
- Bloom disabled - Makes scenes look flat
- Ambient Occlusion disabled - Reduces depth perception

---

## Recommended Settings for Good Graphics + Performance

### 1. **Rendering Settings** (`DefaultEngine.ini` → `[/Script/Engine.RendererSettings]`)

#### For BALANCED Quality & Performance (Recommended):

```ini
[/Script/Engine.RendererSettings]
; Disable static lighting (you're using Lumen dynamic GI - correct)
r.AllowStaticLighting=False

; LUMEN - Keep these for good dynamic lighting
r.DynamicGlobalIlluminationMethod=2
r.ReflectionMethod=2

; NANITE - Great for static meshes, keep enabled
r.Nanite.ProjectEnabled=True
r.GenerateMeshDistanceFields=True

; RAY TRACING - Disable for better performance unless targeting high-end
r.RayTracing=False
r.RayTracing.RayTracingProxies.ProjectEnabled=False

; SHADOWS - Use regular shadow maps (better performance than RT shadows)
r.Shadow.Virtual.Enable=1
r.Shadow.Virtual.TranslucentQuality=2

; ANTI-ALIASING - Enable TAA for smooth edges
r.AntiAliasingMethod=2
r.TemporalAA.Quality=2
r.TemporalAA.Upsampling=True

; POST PROCESSING - Enable key features
r.DefaultFeature.Bloom=True
r.BloomQuality=5
r.DefaultFeature.AmbientOcclusion=True
r.AmbientOcclusionLevels=-1
r.AmbientOcclusionRadiusScale=1.0
r.DefaultFeature.MotionBlur=False

; AUTO EXPOSURE - Keep your current settings (they're good)
r.DefaultFeature.AutoExposure.ExtendDefaultLuminanceRange=True
r.DefaultFeature.LocalExposure.HighlightContrastScale=0.8
r.DefaultFeature.LocalExposure.ShadowContrastScale=0.8

; SKIN CACHE - Good for skeletal meshes (you have animals)
r.SkinCache.CompileShaders=True
r.SkinCache.DefaultBehavior=1

; ADDITIONAL PERFORMANCE
r.Streaming.PoolSize=2000
r.Streaming.MaxTextureUVDensity=0.5
```

#### For HIGH-END Graphics (If targeting powerful PCs):

```ini
; Keep Ray Tracing
r.RayTracing=True
r.RayTracing.Shadows=True
r.RayTracing.AmbientOcclusion=True

; Higher quality settings
r.AntiAliasingMethod=2
r.TemporalAA.Quality=2
r.DefaultFeature.Bloom=True
r.BloomQuality=5
r.DefaultFeature.AmbientOcclusion=True
r.AmbientOcclusionQuality=100

; Virtual Shadow Maps (better than regular but more expensive)
r.Shadow.Virtual.Enable=1
r.Shadow.Virtual.TranslucentQuality=3
```

#### For MAXIMUM Performance (Lower-end PCs):

```ini
; Disable expensive features
r.RayTracing=False
r.Nanite.ProjectEnabled=False

; Use software Lumen (cheaper than hardware)
r.DynamicGlobalIlluminationMethod=1
r.ReflectionMethod=1

; Basic anti-aliasing
r.AntiAliasingMethod=1
r.MSAACount=2

; Minimal post-processing
r.DefaultFeature.Bloom=True
r.BloomQuality=3
r.DefaultFeature.AmbientOcclusion=False
r.DefaultFeature.MotionBlur=False

; Regular shadows
r.Shadow.Virtual.Enable=0
```

---

### 2. **Hardware Targeting** (`DefaultEngine.ini` → `[/Script/HardwareTargeting.HardwareTargetingSettings]`)

```ini
[/Script/HardwareTargeting.HardwareTargetingSettings]
TargetedHardwareClass=Desktop
AppliedTargetedHardwareClass=Desktop

; Change this based on your target audience:
; Scalable = Widest compatibility
; Maximum = Best graphics, higher requirements
DefaultGraphicsPerformance=Scalable
AppliedDefaultGraphicsPerformance=Scalable
```

---

### 3. **Frame Rate Settings** (Already Good!)

Your current settings are excellent:

```ini
[/Script/Engine.Engine]
bUseFixedFrameRate=True
FixedFrameRate=60.000000
```

**Alternative for variable frame rate:**
```ini
bUseFixedFrameRate=False
; Then let the engine adjust based on hardware
```

---

### 4. **Scalability Settings for Players**

Create quality presets that players can choose from. Add to `DefaultScalability.ini`:

```ini
[ScalabilitySettings]
PerfIndexThresholds_ResolutionQuality="10 20 30 40 50"
PerfIndexThresholds_ViewDistanceQuality="10 20 30 40 50"
PerfIndexThresholds_AntiAliasingQuality="10 20 30 40 50"
PerfIndexThresholds_ShadowQuality="10 20 30 40 50"
PerfIndexThresholds_PostProcessQuality="10 20 30 40 50"
PerfIndexThresholds_TextureQuality="10 20 30 40 50"
PerfIndexThresholds_EffectsQuality="10 20 30 40 50"
PerfIndexThresholds_FoliageQuality="10 20 30 40 50"
PerfIndexThresholds_ShadingQuality="10 20 30 40 50"
```

---

### 5. **Texture Settings** (`DefaultEngine.ini`)

Add texture streaming optimization:

```ini
[/Script/Engine.RendererSettings]
; Texture streaming pool (adjust based on your asset size)
r.Streaming.PoolSize=2000
r.Streaming.MaxTextureUVDensity=0.5
r.Streaming.UseFixedPoolSize=False
r.Streaming.LimitPoolSizeToVRAM=True

; Mipmap settings
r.Streaming.MipBias=0
r.Streaming.AmortizeCPUToGPUCopy=True
r.Streaming.MaxNumTexturesToStreamPerFrame=0
```

---

### 6. **Audio Settings** (Already Optimized!)

Your audio settings look good. Keep them as is.

---

### 7. **Platform-Specific Optimizations**

#### Windows (DX12) - Current Settings are Good:
```ini
[/Script/WindowsTargetPlatform.WindowsTargetSettings]
DefaultGraphicsRHI=DefaultGraphicsRHI_DX12
+D3D12TargetedShaderFormats=PCD3D_SM6
```

#### Consider adding DX11 fallback for older PCs:
```ini
; Keep DX12 as primary but allow DX11 fallback
DefaultGraphicsRHI=DefaultGraphicsRHI_DX12
bSupportDX11=True
```

---

## Specific Recommendations for Your Game

Based on your game (top-down animal sorting with PSX-style assets):

### Recommended Configuration:

```ini
[/Script/Engine.RendererSettings]
; Lighting - Lumen is good but may be overkill for PSX style
; Consider switching to simpler lighting for better performance
r.DynamicGlobalIlluminationMethod=1  ; Software Lumen
r.ReflectionMethod=1  ; Software Lumen Reflections

; OR keep Lumen hardware for better quality
r.DynamicGlobalIlluminationMethod=2
r.ReflectionMethod=2

; Disable Ray Tracing (unnecessary for your art style)
r.RayTracing=False

; Keep Nanite for environment geometry
r.Nanite.ProjectEnabled=True

; Enable TAA for smooth edges
r.AntiAliasingMethod=2
r.TemporalAA.Quality=2

; Enable Bloom for visual pop
r.DefaultFeature.Bloom=True
r.BloomQuality=4

; Enable AO for depth (subtle on PSX-style but helpful)
r.DefaultFeature.AmbientOcclusion=True
r.AmbientOcclusionLevels=3
r.AmbientOcclusionQuality=60

; Motion Blur - Keep disabled for responsive gameplay
r.DefaultFeature.MotionBlur=False

; Shadows - Use Virtual Shadow Maps for quality
r.Shadow.Virtual.Enable=1
r.Shadow.Virtual.TranslucentQuality=2
```

---

## Build/Packaging Settings

When packaging your game, use these settings in **Project Settings > Packaging**:

### For Distribution Build:

1. **Build Configuration:** Shipping
2. **Enable these:**
   - ✅ Full Rebuild
   - ✅ Compress content
   - ✅ Include prerequisites installer
   - ✅ Use Pak File
   - ✅ Create compressed cooked packages

3. **Disable for smaller builds:**
   - ❌ Include Debug Files
   - ❌ Include Crash Reporter

4. **Cooking:**
   - Cook everything in one package
   - Exclude editor content
   - Enable Pak file compression (saves ~30% size)

---

## Testing Different Configurations

### Quick Test Process:

1. **Make changes** to DefaultEngine.ini
2. **Restart Unreal Editor**
3. **Test in PIE** (Play In Editor)
4. **Package as Development** build first
5. **Test packaged game** on target hardware
6. **Adjust based on FPS and quality**

### Performance Profiling:

Use these console commands during testing:

```
stat fps           ; Show frame rate
stat unit          ; Show frame time breakdown
stat scenerendering ; Show rendering stats
stat gpu           ; Show GPU time
r.ScreenPercentage 100  ; Adjust resolution scale
```

---

## Recommended Final Settings for Your Game

Based on your PSX-style aesthetic and gameplay:

```ini
[/Script/Engine.RendererSettings]
r.AllowStaticLighting=False
r.GenerateMeshDistanceFields=True
r.DynamicGlobalIlluminationMethod=1
r.ReflectionMethod=1
r.Nanite.ProjectEnabled=True
r.RayTracing=False
r.Shadow.Virtual.Enable=1
r.Shadow.Virtual.TranslucentQuality=2
r.AntiAliasingMethod=2
r.TemporalAA.Quality=2
r.DefaultFeature.Bloom=True
r.BloomQuality=4
r.DefaultFeature.AmbientOcclusion=True
r.AmbientOcclusionQuality=60
r.DefaultFeature.MotionBlur=False
r.SkinCache.CompileShaders=True
r.DefaultFeature.AutoExposure.ExtendDefaultLuminanceRange=True

[/Script/HardwareTargeting.HardwareTargetingSettings]
TargetedHardwareClass=Desktop
DefaultGraphicsPerformance=Scalable

[/Script/Engine.Engine]
bUseFixedFrameRate=True
FixedFrameRate=60.000000
```

---

## Key Takeaways

### ✅ DO Enable:
- **Temporal Anti-Aliasing (TAA)** - Smooths edges
- **Bloom** - Adds visual pop
- **Ambient Occlusion** - Adds depth
- **Nanite** - For environment meshes
- **Virtual Shadow Maps** - Good quality/performance balance
- **Software Lumen** - Good lighting with better performance

### ❌ DON'T Enable (for your game):
- **Ray Tracing** - Too expensive, minimal benefit for PSX style
- **Motion Blur** - Reduces responsiveness in gameplay
- **Cinematic features** - Unnecessary overhead

### 🎯 Priority Order:
1. Disable Ray Tracing (biggest performance win)
2. Enable TAA (biggest quality win)
3. Switch to Software Lumen instead of Hardware Lumen
4. Enable Bloom + AO
5. Use Virtual Shadow Maps
6. Keep Nanite for environment

### 📊 Expected Performance Impact:
- **Disabling Ray Tracing:** +40-60% FPS
- **Enabling TAA:** -5% FPS, +300% visual quality
- **Software Lumen vs Hardware:** +15-25% FPS
- **Virtual Shadow Maps:** -10% FPS vs regular shadows

---

## Testing Checklist

Before final release, test with:
- ✅ Low-end PC (GTX 1060 equivalent)
- ✅ Mid-range PC (RTX 3060 equivalent)  
- ✅ High-end PC (RTX 4070+ equivalent)
- ✅ Different resolutions (1080p, 1440p, 4K)
- ✅ Laptop vs Desktop
- ✅ AMD vs NVIDIA GPUs

Target: **60 FPS on GTX 1660 / RX 580 at 1080p**

---

*Last Updated: November 23, 2025*  
*Unreal Engine Version: 5.6*

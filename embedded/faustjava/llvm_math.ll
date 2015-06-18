; ModuleID = 'src/llvm_math.c'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"

define i8* @llvm_malloc(i64 %size) nounwind uwtable ssp {
entry:
  %size.addr = alloca i64, align 8
  store i64 %size, i64* %size.addr, align 8
  %0 = load i64* %size.addr, align 8
  %call1 = call i8* @malloc(i64 %0)
  ret i8* %call1
}

declare i8* @malloc(i64)

define void @llvm_free(i8* %ptr) nounwind uwtable ssp {
entry:
  %ptr.addr = alloca i8*, align 8
  store i8* %ptr, i8** %ptr.addr, align 8
  %0 = load i8** %ptr.addr, align 8
  call void @free(i8* %0)
  ret void
}

declare void @free(i8*)

define float @fabsf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @fabs(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @fabs(double)

define float @acosf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @acos(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @acos(double)

define float @asinf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @asin(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @asin(double)

define float @atanf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @atan(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @atan(double)

define float @atan2f(float %x, float %y) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  %y.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  store float %y, float* %y.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %1 = load float* %y.addr, align 4
  %conv1 = fpext float %1 to double
  %call = call double @atan2(double %conv, double %conv1)
  %conv2 = fptrunc double %call to float
  ret float %conv2
}

declare double @atan2(double, double)

define float @ceilf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @ceil(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @ceil(double)

define float @cosf(float %x) nounwind uwtable readnone ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @cos(double %conv) nounwind readnone
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @cos(double) nounwind readnone

define float @coshf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @cosh(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @cosh(double)

define float @expf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @exp(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @exp(double)

define float @floorf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @floor(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @floor(double)

define float @fmodf(float %x, float %y) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  %y.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  store float %y, float* %y.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %1 = load float* %y.addr, align 4
  %conv1 = fpext float %1 to double
  %call = call double @fmod(double %conv, double %conv1)
  %conv2 = fptrunc double %call to float
  ret float %conv2
}

declare double @fmod(double, double)

define float @logf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @log(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @log(double)

define float @log10f(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @log10(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @log10(double)

define float @powf(float %x, float %y) nounwind uwtable readnone ssp {
entry:
  %x.addr = alloca float, align 4
  %y.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  store float %y, float* %y.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %1 = load float* %y.addr, align 4
  %conv1 = fpext float %1 to double
  %2 = call double @llvm.pow.f64(double %conv, double %conv1)
  %conv2 = fptrunc double %2 to float
  ret float %conv2
}

declare double @llvm.pow.f64(double, double) nounwind readonly

define float @roundf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @round(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @round(double)

define float @sinf(float %x) nounwind uwtable readnone ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @sin(double %conv) nounwind readnone
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @sin(double) nounwind readnone

define float @sinhf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @sinh(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @sinh(double)

define float @sqrtf(float %x) nounwind uwtable readnone ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @sqrt(double %conv) nounwind readnone
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @sqrt(double) nounwind readnone

define float @tanf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @tan(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @tan(double)

define float @tanhf(float %x) nounwind uwtable ssp {
entry:
  %x.addr = alloca float, align 4
  store float %x, float* %x.addr, align 4
  %0 = load float* %x.addr, align 4
  %conv = fpext float %0 to double
  %call = call double @tanh(double %conv)
  %conv1 = fptrunc double %call to float
  ret float %conv1
}

declare double @tanh(double)

; ModuleID = 'LLVMDialectModule'
source_filename = "LLVMDialectModule"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@nl = internal constant [2 x i8] c"\0A\00"
@frmt_spec = internal constant [4 x i8] c"%f \00"

declare i8* @malloc(i64)

declare void @free(i8*)

declare i32 @printf(i8*, ...)

define void @main() {
  %1 = call i8* @malloc(i64 mul (i64 ptrtoint (double* getelementptr (double, double* null, i64 1) to i64), i64 6))
  %2 = bitcast i8* %1 to double*
  %3 = insertvalue { double*, i64, [2 x i64], [2 x i64] } undef, double* %2, 0
  %4 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %3, i64 0, 1
  %5 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %4, i64 2, 2, 0
  %6 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %5, i64 3, 3, 0
  %7 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %6, i64 3, 2, 1
  %8 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %7, i64 1, 3, 1
  %9 = call i8* @malloc(i64 mul (i64 ptrtoint (double* getelementptr (double, double* null, i64 1) to i64), i64 6))
  %10 = bitcast i8* %9 to double*
  %11 = insertvalue { double*, i64, [2 x i64], [2 x i64] } undef, double* %10, 0
  %12 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %11, i64 0, 1
  %13 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %12, i64 2, 2, 0
  %14 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %13, i64 3, 3, 0
  %15 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %14, i64 3, 2, 1
  %16 = insertvalue { double*, i64, [2 x i64], [2 x i64] } %15, i64 1, 3, 1
  %17 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %18 = getelementptr double, double* %17, i64 0
  store double 1.000000e+00, double* %18
  %19 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %20 = getelementptr double, double* %19, i64 1
  store double 2.000000e+00, double* %20
  %21 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %22 = getelementptr double, double* %21, i64 2
  store double 3.000000e+00, double* %22
  %23 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %24 = getelementptr double, double* %23, i64 3
  store double 4.000000e+00, double* %24
  %25 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %26 = getelementptr double, double* %25, i64 4
  store double 5.000000e+00, double* %26
  %27 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %28 = getelementptr double, double* %27, i64 5
  store double 6.000000e+00, double* %28
  br label %29

29:                                               ; preds = %59, %0
  %30 = phi i64 [ 0, %0 ], [ %60, %59 ]
  %31 = icmp slt i64 %30, 2
  br i1 %31, label %32, label %61

32:                                               ; preds = %29
  br label %33

33:                                               ; preds = %36, %32
  %34 = phi i64 [ 0, %32 ], [ %58, %36 ]
  %35 = icmp slt i64 %34, 3
  br i1 %35, label %36, label %59

36:                                               ; preds = %33
  %37 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %38 = mul i64 %30, 3
  %39 = add i64 0, %38
  %40 = mul i64 %34, 1
  %41 = add i64 %39, %40
  %42 = getelementptr double, double* %37, i64 %41
  %43 = load double, double* %42
  %44 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %45 = mul i64 %30, 3
  %46 = add i64 0, %45
  %47 = mul i64 %34, 1
  %48 = add i64 %46, %47
  %49 = getelementptr double, double* %44, i64 %48
  %50 = load double, double* %49
  %51 = fadd double %43, %50
  %52 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %8, 0
  %53 = mul i64 %30, 3
  %54 = add i64 0, %53
  %55 = mul i64 %34, 1
  %56 = add i64 %54, %55
  %57 = getelementptr double, double* %52, i64 %56
  store double %51, double* %57
  %58 = add i64 %34, 1
  br label %33

59:                                               ; preds = %33
  %60 = add i64 %30, 1
  br label %29

61:                                               ; preds = %29
  br label %62

62:                                               ; preds = %79, %61
  %63 = phi i64 [ 0, %61 ], [ %81, %79 ]
  %64 = icmp slt i64 %63, 2
  br i1 %64, label %65, label %82

65:                                               ; preds = %62
  br label %66

66:                                               ; preds = %69, %65
  %67 = phi i64 [ 0, %65 ], [ %78, %69 ]
  %68 = icmp slt i64 %67, 3
  br i1 %68, label %69, label %79

69:                                               ; preds = %66
  %70 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %8, 0
  %71 = mul i64 %63, 3
  %72 = add i64 0, %71
  %73 = mul i64 %67, 1
  %74 = add i64 %72, %73
  %75 = getelementptr double, double* %70, i64 %74
  %76 = load double, double* %75
  %77 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @frmt_spec, i64 0, i64 0), double %76)
  %78 = add i64 %67, 1
  br label %66

79:                                               ; preds = %66
  %80 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @nl, i64 0, i64 0))
  %81 = add i64 %63, 1
  br label %62

82:                                               ; preds = %62
  %83 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %16, 0
  %84 = bitcast double* %83 to i8*
  call void @free(i8* %84)
  %85 = extractvalue { double*, i64, [2 x i64], [2 x i64] } %8, 0
  %86 = bitcast double* %85 to i8*
  call void @free(i8* %86)
  ret void
}


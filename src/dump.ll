; ModuleID = 'Decaf compiler jit'

@data = global [100 x i32] zeroinitializer
@i = common global i32 0, align 4
@sum = common global i32 0, align 4
@x1 = common global i32 0, align 4
@x2 = common global i32 0, align 4
@a = common global i32 0, align 4
@micchkec = common global i32 0, align 4
@b = common global i32 0, align 4
@saisr = common global i32 0, align 4
@hello = common global i32 0, align 4
@this = common global i32 0, align 4
@j = common global i32 0, align 4
@somubha = common global i32 0, align 4
@0 = private unnamed_addr constant [3 x i8] c"%d\00"
@1 = private unnamed_addr constant [7 x i8] c"hi %d\0A\00"
@2 = private unnamed_addr constant [3 x i8] c"%d\00"
@3 = private unnamed_addr constant [10 x i8] c"hllii %d\0A\00"
@4 = private unnamed_addr constant [10 x i8] c"hllii %d\0A\00"
@5 = private unnamed_addr constant [8 x i8] c"hii %d\0A\00"
@6 = private unnamed_addr constant [10 x i8] c"hllii %d\0A\00"
@7 = private unnamed_addr constant [8 x i8] c"fda %d\0A\00"
@8 = private unnamed_addr constant [4 x i8] c"%d\0A\00"

define i32 @main() {
entry:
  %0 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i32* @this)
  %1 = load i32, i32* @this
  %2 = call i32 @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @1, i32 0, i32 0), i32 %1)
  br label %l1

l1:                                               ; preds = %got, %entry
  store i32 1, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @data, i32 0, i32 3)
  store i32 1, i32* @i
  %3 = load i32, i32* @i
  br i1 true, label %loop, label %afterloop

got:                                              ; No predecessors!
  %4 = call i32 @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @2, i32 0, i32 0), i32* getelementptr inbounds ([100 x i32], [100 x i32]* @data, i32 0, i32 2))
  %5 = load i32, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @data, i32 0, i32 2)
  %6 = call i32 @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @3, i32 0, i32 0), i32 %5)
  store i32 8, i32* @a
  %7 = load i32, i32* @a
  %8 = call i32 @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @4, i32 0, i32 0), i32 %7)
  %9 = load i32, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @data, i32 0, i32 2)
  %10 = load i32, i32* getelementptr inbounds ([100 x i32], [100 x i32]* @data, i32 0, i32 0)
  %addtmp = add i32 %9, %10
  store i32 %addtmp, i32* @x1
  br label %l1

loop:                                             ; preds = %loop, %l1
  %11 = load i32, i32* @i
  %12 = call i32 @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @5, i32 0, i32 0), i32 %11)
  %13 = load i32, i32* @i
  %next = add i32 %13, 1
  store i32 %next, i32* @i
  %loopcond = icmp ule i32 %next, 5
  br i1 %loopcond, label %loop, label %afterloop

afterloop:                                        ; preds = %loop, %l1
  %14 = load i32, i32* @x1
  %15 = call i32 @printf(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @6, i32 0, i32 0), i32 %14)
  %16 = load i32, i32* @a
  %17 = call i32 @printf(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @7, i32 0, i32 0), i32 %16)
  %18 = load i32, i32* @a
  %data_Index = getelementptr [100 x i32], [100 x i32]* @data, i32 0, i32 %18
  %19 = load i32, i32* @a
  %data_Index1 = getelementptr [100 x i32], [100 x i32]* @data, i32 0, i32 %19
  %20 = load i32, i32* %data_Index1
  %addtmp2 = add i32 %20, 1
  store i32 %addtmp2, i32* %data_Index
  %21 = load i32, i32* @a
  %data_Index3 = getelementptr [100 x i32], [100 x i32]* @data, i32 0, i32 %21
  %22 = load i32, i32* %data_Index3
  %23 = call i32 @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @8, i32 0, i32 0), i32 %22)
  ret i32 0
}

declare i32 @scanf(i8*, i32*)

declare i32 @printf(i8*, i32)

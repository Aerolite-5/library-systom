# 实验一、二、三、四：图书借阅管理系统

## 类设计

本版本在实验三基础上只增加了 `Magazine`、`Student`、`Teacher` 三个后续实验六会保留的类，没有一次性把后续类全部加完：

```text
Resource（抽象基类）
├─ Book（图书，有库存）
├─ Magazine（杂志，有库存）
└─ ES（电子资源，无库存）

Reader（抽象基类）
├─ Student（学生）
└─ Teacher（教师）

BorrowRecord（借阅记录）
Library（管理类）
```

共 9 个类。

## 八个功能

1. 添加资源（图书 / 杂志 / 电子资源）
2. 增加库存
3. 借书
4. 还书
5. 查看资源
6. 查询资源
7. 查看读者
8. 查看借阅记录

## 实验三内容：继承与派生

- `Book`、`Magazine`、`ES` 都继承 `Resource`；
- `Book`、`Magazine` 有库存，借出减少、归还增加；
- `ES` 没有库存，借阅不减少任何数量，可以多人同时借阅。

## 实验四内容：多态性与虚函数

`Resource` 提供纯虚函数：

```cpp
virtual std::string Type() const = 0;
virtual bool IsDigital() const = 0;
virtual bool CanBorrow() const = 0;
virtual void OnBorrow() = 0;
virtual void OnReturn() = 0;
virtual std::string BorrowMessage() const = 0;
virtual void Show() const = 0;
```

- `Library` 用 `std::vector<Resource*>` 和 `std::vector<Reader*>` 保存对象；
- 借书时通过 `Resource*` 调用 `CanBorrow()`、`OnBorrow()`、`BorrowMessage()`；
- 查看资源时通过 `Resource*` 调用 `Show()`；
- 查看读者时通过 `Reader*` 调用 `Show()`；
- 增加库存时通过 `Resource*` 调用 `AddStock()`，`Book`、`Magazine` 重写，`ES` 使用基类默认实现；
- 不再用 `dynamic_cast` 判断具体资源类型，由虚函数在运行时决定调用版本。

## 暂不加入的类

为了给实验五、实验六留空间，本版本暂不加入：

- `PhysicalResource`
- `FineBill`
- `Category`
- `ResourceCatalog`、`ReaderRegistry`、`LoanService`、`FineService`

## 预置读者

```text
5120250001 胡鑫  学生  计算机学院  最多借 5 项
5120250002 高斌  学生  文学院    最多借 5 项
5120256423 张想  学生  历史学院  最多借 5 项
T2025001   李文  教师  计算机学院 副教授  最多借 10 项
```

## 运行

打开 `Last library systom.slnx`，选择 `x64` 配置编译运行。

Debug x64 和 Release x64 均已编译通过。

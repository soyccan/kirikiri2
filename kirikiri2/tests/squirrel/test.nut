local a=10;
local b = ::krkr.a;
local c = ::krkr.b;
::krkr.c = 100;

test <- "�Ă��Ƃ̃e�L�X�g";


class Foo {

	//constructor
	constructor()
	{
		testy = ["stuff",1,2,3];
	}

	//member function
	function print()
	{
		foreach(i,val in testy)
		{
			::print("idx = "+i+" = "+val+" \n");
		}
	}
	//property
	testy = null;
	data="testdata";
};

function hoge()
{
	print("�t�@���N�V�����Ăяo��!");
}

function main(tick)
{
	print("tick�l:" + tick);
}

// �t�@�C���Ăяo���e�X�g
dofile("test2.nut");

// �t�@�C���������݃e�X�g
local f = file("output", "w");
f.writen(10, 'l');
f = null;

// ���w�֐��e�X�g
print("sin(PI):" + sin(PI));
print("rand():" + rand());

// ������֐��e�X�g
print(format("%s %d 0x%02X","this is a test :",123,10));

// �g���g�����̃I�u�W�F�N�g����
local layer2 = ::krkr.MyLayer(::krkr.win, ::krkr.base);
layer2.setSize(100,100);
layer2.setPos(100,100);
layer2.fillRect(0,0,100,100,0xff00ff00);
layer2.visible = true;
return layer2;
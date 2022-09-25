unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, math;

type
  TForm1 = class(TForm)
    Button1: TButton;
    procedure Button1Click(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure fract(x,y,a,l,k,a1:integer);
var
  p:integer;
begin
  p := a1;
  if k mod 2 = 0 then
    p := -a1;
  while l > 3 do
  begin
    with form1.Canvas do
    begin
      pen.Width := 6-k;
      pen.Color := rgb(random(255),random(255),random(255));
      moveto(x,y);
      lineto(x+round(cos(degtorad(a))*l),y+round(sin(degtorad(a))*l));
      x := x+round(cos(degtorad(a))*l);
      y := y+round(sin(degtorad(a))*l);
      a := a + p;
      l := round(l / 1.17);
      fract(x,y,a-(p*2),round(l / 1.2),k+1,a1+1);
    end;
  end;
end;

procedure TForm1.Button1Click(Sender: TObject);
begin
  fract(400,500,270,100,0,20);
end;

end.

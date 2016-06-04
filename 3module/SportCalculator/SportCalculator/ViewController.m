//
//  ViewController.m
//  SportCalculator
//
//  Created by Дмитрий  Загребаев on 02.06.16.
//  Copyright © 2016 Дмитрий  Загребаев. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
{
    int test;
}

@property (weak, nonatomic) IBOutlet UITextField *myField;
@property (weak, nonatomic) IBOutlet UIButton *myButton;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)Test:(UIButton *)sender
{
    [self.myButton setTitle:self.myField.text forState:UIControlStateNormal];
    NSLog(@"%@", self.myField.text);
}

-(void)getInstanceOfLength:(int)length Width:(int)width
{
    
}

@end

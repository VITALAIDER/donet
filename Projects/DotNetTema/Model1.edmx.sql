
-- --------------------------------------------------
-- Entity Designer DDL Script for SQL Server 2005, 2008, 2012 and Azure
-- --------------------------------------------------
-- Date Created: 03/05/2017 20:30:31
-- Generated from EDMX file: c:\users\sava\documents\visual studio 2015\Projects\DotNetTema\Model1.edmx
-- --------------------------------------------------

SET QUOTED_IDENTIFIER OFF;
GO
USE [RentACarSystem];
GO
IF SCHEMA_ID(N'dbo') IS NULL EXECUTE(N'CREATE SCHEMA [dbo]');
GO

-- --------------------------------------------------
-- Dropping existing FOREIGN KEY constraints
-- --------------------------------------------------


-- --------------------------------------------------
-- Dropping existing tables
-- --------------------------------------------------


-- --------------------------------------------------
-- Creating all tables
-- --------------------------------------------------

-- Creating table 'Companies'
CREATE TABLE [dbo].[Companies] (
    [CompanyId] int IDENTITY(1,1) NOT NULL,
    [CompanyName] nvarchar(max)  NOT NULL,
    [CompanyContact_ContactId] int  NOT NULL
);
GO

-- Creating table 'Cars'
CREATE TABLE [dbo].[Cars] (
    [CarId] int IDENTITY(1,1) NOT NULL,
    [BrandName] nvarchar(max)  NOT NULL,
    [ModelName] nvarchar(max)  NOT NULL,
    [CompanyCompanyId] int  NOT NULL
);
GO

-- Creating table 'Users'
CREATE TABLE [dbo].[Users] (
    [UserId] int IDENTITY(1,1) NOT NULL,
    [FirstName] nvarchar(max)  NOT NULL,
    [LastName] nvarchar(max)  NOT NULL,
    [Phone] nvarchar(max)  NOT NULL,
    [CompanyCompanyId] int  NOT NULL
);
GO

-- Creating table 'CompanyContacts'
CREATE TABLE [dbo].[CompanyContacts] (
    [ContactId] int IDENTITY(1,1) NOT NULL,
    [Adress] nvarchar(max)  NOT NULL,
    [Phone] nvarchar(max)  NOT NULL
);
GO

-- Creating table 'CarUser'
CREATE TABLE [dbo].[CarUser] (
    [Cars_CarId] int  NOT NULL,
    [Users_UserId] int  NOT NULL
);
GO

-- --------------------------------------------------
-- Creating all PRIMARY KEY constraints
-- --------------------------------------------------

-- Creating primary key on [CompanyId] in table 'Companies'
ALTER TABLE [dbo].[Companies]
ADD CONSTRAINT [PK_Companies]
    PRIMARY KEY CLUSTERED ([CompanyId] ASC);
GO

-- Creating primary key on [CarId] in table 'Cars'
ALTER TABLE [dbo].[Cars]
ADD CONSTRAINT [PK_Cars]
    PRIMARY KEY CLUSTERED ([CarId] ASC);
GO

-- Creating primary key on [UserId] in table 'Users'
ALTER TABLE [dbo].[Users]
ADD CONSTRAINT [PK_Users]
    PRIMARY KEY CLUSTERED ([UserId] ASC);
GO

-- Creating primary key on [ContactId] in table 'CompanyContacts'
ALTER TABLE [dbo].[CompanyContacts]
ADD CONSTRAINT [PK_CompanyContacts]
    PRIMARY KEY CLUSTERED ([ContactId] ASC);
GO

-- Creating primary key on [Cars_CarId], [Users_UserId] in table 'CarUser'
ALTER TABLE [dbo].[CarUser]
ADD CONSTRAINT [PK_CarUser]
    PRIMARY KEY CLUSTERED ([Cars_CarId], [Users_UserId] ASC);
GO

-- --------------------------------------------------
-- Creating all FOREIGN KEY constraints
-- --------------------------------------------------

-- Creating foreign key on [CompanyCompanyId] in table 'Cars'
ALTER TABLE [dbo].[Cars]
ADD CONSTRAINT [FK_CompanyCar]
    FOREIGN KEY ([CompanyCompanyId])
    REFERENCES [dbo].[Companies]
        ([CompanyId])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_CompanyCar'
CREATE INDEX [IX_FK_CompanyCar]
ON [dbo].[Cars]
    ([CompanyCompanyId]);
GO

-- Creating foreign key on [CompanyContact_ContactId] in table 'Companies'
ALTER TABLE [dbo].[Companies]
ADD CONSTRAINT [FK_CompanyCompanyContact]
    FOREIGN KEY ([CompanyContact_ContactId])
    REFERENCES [dbo].[CompanyContacts]
        ([ContactId])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_CompanyCompanyContact'
CREATE INDEX [IX_FK_CompanyCompanyContact]
ON [dbo].[Companies]
    ([CompanyContact_ContactId]);
GO

-- Creating foreign key on [CompanyCompanyId] in table 'Users'
ALTER TABLE [dbo].[Users]
ADD CONSTRAINT [FK_CompanyUser]
    FOREIGN KEY ([CompanyCompanyId])
    REFERENCES [dbo].[Companies]
        ([CompanyId])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_CompanyUser'
CREATE INDEX [IX_FK_CompanyUser]
ON [dbo].[Users]
    ([CompanyCompanyId]);
GO

-- Creating foreign key on [Cars_CarId] in table 'CarUser'
ALTER TABLE [dbo].[CarUser]
ADD CONSTRAINT [FK_CarUser_Car]
    FOREIGN KEY ([Cars_CarId])
    REFERENCES [dbo].[Cars]
        ([CarId])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating foreign key on [Users_UserId] in table 'CarUser'
ALTER TABLE [dbo].[CarUser]
ADD CONSTRAINT [FK_CarUser_User]
    FOREIGN KEY ([Users_UserId])
    REFERENCES [dbo].[Users]
        ([UserId])
    ON DELETE NO ACTION ON UPDATE NO ACTION;
GO

-- Creating non-clustered index for FOREIGN KEY 'FK_CarUser_User'
CREATE INDEX [IX_FK_CarUser_User]
ON [dbo].[CarUser]
    ([Users_UserId]);
GO

-- --------------------------------------------------
-- Script has ended
-- --------------------------------------------------
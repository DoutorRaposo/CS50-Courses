# Generated by Django 4.2.6 on 2023-10-30 17:07

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('auctions', '0002_categories_listings_category'),
    ]

    operations = [
        migrations.RenameModel(
            old_name='Categories',
            new_name='Category',
        ),
        migrations.RenameModel(
            old_name='Comments',
            new_name='Comment',
        ),
        migrations.RenameModel(
            old_name='Listings',
            new_name='Listing',
        ),
    ]
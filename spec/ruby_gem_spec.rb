# frozen_string_literal: true

RSpec.describe RubyGem do
  it 'has a version number' do
    expect(RubyGem::VERSION).not_to be nil
  end

  RUBY_GEM_FIELDS = %i[
    NAME
    AUTHORS
    SUMMARY
    HOMEPAGE
    SOURCE_CODE_URI
    CHANGELOG_URI
    DESCRIPTION
  ].freeze

  RUBY_GEM_FIELDS.each do |field_name|
    value = RubyGem.const_defined?(field_name) &&
            RubyGem.const_get(field_name)

    default_value_field_name = :"DEFAULT_#{field_name}"
    default_value = RubyGem.const_defined?(default_value_field_name) &&
                    RubyGem.const_get(default_value_field_name)

    it "does not use the default #{field_name} value in lib/ruby_gem.rb",
       unless: value.nil? && default_value.nil? \
    do
      expect(value).not_to eq default_value
    end
  end
end

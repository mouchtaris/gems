# frozen_string_literal: true

RSpec.describe Buffer do
  it 'has a version number' do
    expect(Buffer::VERSION).not_to be nil
  end
end
